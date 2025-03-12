#include <serio.h>
#include <s3k.h>

void main(void)
{
	while (1) {
		// Print 1 then sleep.
		serio_putstr("1");
		s3k_sleep(0);
	}
}
