# EECS581 Assignment 1 - AI Generated IPv4 Extraction

**Model used: Claude Sonnet 5**

To begin with, I wrote a shell program in extract.c with comments fencing off
the areas that I wanted the AI to fill in. Everything outside the comment markers
was hand-written before the AI was consulted. The extractIPv4 signature and
its doc comments were copied from the Canvas page. I wrote the Makefile and set up the
test case, which is based on the sample run on Canvas. I added one extra case to
verify that a port more than 5 digits long is rejected.

I ran Claude Code in manual mode and reviewed every individual edit before accepting.
The tests passed after only one prompt, which I'd attribute to Sonnet 5 being a
powerful model, and my prompt being carefully constructed to cover requirements and
edge-cases.

## Prompts
- 9/27/2026 @ 6:04 PM
```
Boilerplate for a C program that extracts IPv4 addresses from lines of
noisy input has been provided. Your job is to fill in the extractIPv4 function.
A handful of standard library utilities which trivialize this are forbidden,
including: Any string-to-number conversion function such as atoi or scanf,
any address-parsing utilities, as well as regex.h or similar. Do not touch lines
outside of the comment-fenced areas for AI-generated code. Address octets may not
have leading zeroes unless the whole octet is 0. Ports are optional, and can only
be between 0 and 65535, following a single colon. If the colon is present, then
the following characters must form a valid port, or else the whole address should
be rejected. Stray periods or colons adjacent to an otherwise valid address
invalidate the match.
```
