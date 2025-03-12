#include <serio.h>
#include <s3k.h>

#define RAM_MEM_CAP 1
#define UART_MEM_CAP 2
#define TIME_CAP 4
#define MONITOR_CAP 5

void setup_uart(void)
{
	uint64_t uart_addr = (uint64_t)(_serio_out->base);
	uint64_t uart_size = 0x20;
	s3k_cap_t pmp_uart = s3k_mk_pmp(s3k_napot_encode(uart_addr, uart_size), S3K_MEM_RW);
	s3k_cap_derive(UART_MEM_CAP, 9, pmp_uart);
	s3k_pmp_load(9, 1);
	s3k_sync();
}

void setup_app1(void)
{
	// Process ID of app1
	s3k_pid_t app1_pid = 1;
	// The memory range of app1
	uint64_t app1_addr = 0x80020000;
	uint64_t app1_size = 0x10000;
	// The memory range for uart driver
	uint64_t uart_addr = (uint64_t)(_serio_out->base);
	uint64_t uart_size = 0x20;

	// Derive and send capability for RAM memory.
	s3k_cap_t pmp_ram = s3k_mk_pmp(s3k_napot_encode(app1_addr, app1_size), S3K_MEM_RWX);
	s3k_cap_derive(RAM_MEM_CAP, 10, pmp_ram);
	s3k_mon_cap_send(MONITOR_CAP, 10, app1_pid, 0);
	s3k_mon_pmp_load(MONITOR_CAP, app1_pid, 0, 0);

	// Delete memory capability, prevents app0 from revoking RAM memory of app1
	s3k_cap_delete(RAM_MEM_CAP);

	// Derive and send capability for UART memory.
	s3k_cap_t pmp_uart = s3k_mk_pmp(s3k_napot_encode(uart_addr, uart_size), S3K_MEM_RW);
	s3k_cap_derive(UART_MEM_CAP, 10, pmp_uart);
	s3k_mon_cap_send(MONITOR_CAP, 10, app1_pid, 1);
	s3k_mon_pmp_load(MONITOR_CAP, app1_pid, 1, 1);
	// Delete memory capability, prevents app0 from revoking UART memory of app1
	s3k_cap_delete(UART_MEM_CAP);

	// Derive and send capability for time.
	s3k_cap_t app0_time = s3k_mk_time(0, 0, NSLOT/ 2); 
	s3k_cap_t app1_time = s3k_mk_time(0, NSLOT / 2, NSLOT); 

	// First (NSLOT / 2) slots kept by app0.
	s3k_cap_derive(TIME_CAP, 10, app0_time);

	// Last (NSLOT / 2) slots sent to app1.
	s3k_cap_derive(TIME_CAP, 11, app1_time);
	s3k_mon_cap_send(MONITOR_CAP, 11, app1_pid, 2);
	// Delete orignal capability of app1, prevents app0 from revoking the time of app1.
	s3k_cap_delete(TIME_CAP);

	// Set the PC of app1.
	s3k_mon_reg_write(MONITOR_CAP, app1_pid, S3K_REG_PC, app1_addr);
	// Starts app1
	s3k_mon_resume(MONITOR_CAP, app1_pid);

	// Remove monitor capability, preventing app0 from interacting with app1.
	s3k_cap_delete(MONITOR_CAP);
	s3k_sync();
}

void main(void)
{
	setup_uart();
	setup_app1();
	while (1) {
		// Print 0 then sleep.
		serio_putstr("0");
		s3k_sleep(0);
	}
}
