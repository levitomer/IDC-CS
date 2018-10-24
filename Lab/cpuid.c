#include <stdio.h>
#include <string.h>

static void CPUID(int *eax, int *ebx, int *ecx, int *edx)
{
	__asm__ volatile("cpuid": "=a" (*eax),
			"=b" (*ebx),
			"=c" (*ecx),
			"=d" (*edx) : "0" (*eax),
			"2" (*ecx) : "memory");
}

int main()
{
	int eax = 0, ebx, ecx, edx;
	char vendor[13];
	
	CPUID(&eax, &ebx, &ecx, &edx);
	printf("EAX: %08X EBX: %08X ECX: %08X EDX: %08X\n", eax, ebx, ecx, edx);

	
	memcpy(vendor, &ebx, 4);
	memcpy(vendor+4, &edx, 4);
	memcpy(vendor+8, &ecx, 4);
	vendor[12] = '\0';
	
	printf("%s\n", vendor);
	
	return (0);
}
