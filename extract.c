#include <stdio.h>
#include <string.h>

// Provided space for AI-generated helpers
// -- BEGIN AI GENERATED CODE --

static int isDigitChar(char c) {
	return c >= '0' && c <= '9';
}

// Parses the maximal run of digits at s[*idx] as an IPv4 octet (0-255,
// no leading zero unless the octet is exactly "0"). On success, advances
// *idx past the digits and stores the value in *outVal.
static int parseOctet(const char* s, int* idx, unsigned long* outVal) {
	int start = *idx;
	int len = 0;
	while (isDigitChar(s[start + len])) len++;
	if (len == 0 || len > 3) return 0;
	if (len > 1 && s[start] == '0') return 0;

	unsigned long val = 0;
	for (int i = 0; i < len; i++) {
		val = val * 10 + (unsigned long)(s[start + i] - '0');
	}
	if (val > 255) return 0;

	*outVal = val;
	*idx = start + len;
	return 1;
}

// Parses the maximal run of digits at s[*idx] as a port (0-65535). On
// success, advances *idx past the digits and stores the value in *outVal.
static int parsePort(const char* s, int* idx, int* outVal) {
	int start = *idx;
	int len = 0;
	while (isDigitChar(s[start + len])) len++;
	if (len == 0) return 0;

	unsigned long val = 0;
	for (int i = 0; i < len; i++) {
		val = val * 10 + (unsigned long)(s[start + i] - '0');
		if (val > 65535) return 0;
	}

	*outVal = (int)val;
	*idx = start + len;
	return 1;
}

// -- END AI GENERATED CODE --

// Returns 1 if a valid address was found, 0 otherwise.
// On success: *outAddress holds the 32-bit value, and
// *outPort holds the port number, or -1 if no port was present.
// On failure: *outAddress is set to 0 and *outPort is set to -1.
int extractIPv4(const char* str, unsigned long* outAddress, int* outPort) {
	// -- BEGIN AI GENERATED CODE --
	*outAddress = 0;
	*outPort = -1;

	int len = (int)strlen(str);
	for (int i = 0; i < len; i++) {
		if (!isDigitChar(str[i])) continue;
		if (i > 0 && isDigitChar(str[i - 1])) continue;

		int idx = i;
		unsigned long octets[4];
		int ok = 1;
		for (int o = 0; o < 4; o++) {
			if (o > 0) {
				if (str[idx] != '.') { ok = 0; break; }
				idx++;
			}
			if (!parseOctet(str, &idx, &octets[o])) { ok = 0; break; }
		}
		if (!ok) continue;

		if (i > 0 && (str[i - 1] == '.' || str[i - 1] == ':')) continue;

		int port = -1;
		if (str[idx] == ':') {
			int portIdx = idx + 1;
			if (!parsePort(str, &portIdx, &port)) continue;
			idx = portIdx;
		}

		if (str[idx] == '.' || str[idx] == ':') continue;

		*outAddress = (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
		*outPort = port;
		return 1;
	}

	return 0;
	// -- END AI GENERATED CODE --
}

int main() {
	char buffer[1024] = {0};
	unsigned long outAddress = 0;
	int outPort = -1;
	while (1) {
		fputs("Enter a string (or 'END' to quit): ", stdout);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
		if (strcmp(buffer, "END\n") == 0) {
			fputs("Program terminated.\n", stdout);
			break;
		}
		if (extractIPv4(buffer, &outAddress, &outPort)) {
			printf("Extracted IPv4 address: %lu.%lu.%lu.%lu (decimal value: %lu, port: ",
					(outAddress >> 24) & 0xFF, (outAddress >> 16) & 0xFF,
					(outAddress >> 8) & 0xFF, outAddress & 0xFF, outAddress);
			if (outPort == -1)
				printf("none)\n");
			else
				printf("%d)\n", outPort);
		} else {
			fputs("Invalid input: no valid IPv4 address found\n", stdout);
		}
	}
	return 0;
}
