// The algorithm is based on this answer:
//https://stackoverflow.com/questions/955484/is-it-possible-to-convert-utf32-text-to-utf16-using-only-windows-api
//
unsigned int convertUTF32ToUTF16(const char32_t *input, size_t input_size, char16_t *output)
{
	char16_t *start = output;
	const char32_t * const end = input + input_size;
	while (input < end) {
		const char32_t cUTF32 = *input++;
		if (cUTF32 < 0x10000)
		{
			*output++ = cUTF32;
		}
		else {
			unsigned int t = cUTF32 - 0x10000;
			char32_t h = (((t << 12) >> 22) + 0xD800);
			char32_t l = (((t << 22) >> 22) + 0xDC00);
			*output++ = h;
			*output++ = (l & 0x0000FFFF);
		}
	}
	return (output - start) * 2; // size in bytes
}
