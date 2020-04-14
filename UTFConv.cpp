inline int is_high_surrogate(char16_t uc) { return (uc & 0xfffffc00) == 0xd800; }
inline int is_low_surrogate(char16_t uc) { return (uc & 0xfffffc00) == 0xdc00; }

inline char32_t surrogate_to_utf32(char16_t high, char16_t low) {
	return (high << 10) + low - 0x35fdc00;
}

// The algorithm is based on this answer:
//https://stackoverflow.com/a/23920015/2134488
//
void convertUTF16ToUTF32(const char16_t *input,
	size_t input_size,
	char32_t *output)
{
	const char16_t * const end = input + input_size;
	while (input < end) {
		const char16_t uc = *input++;
		if (!((uc - 0xd800u) < 2048u)) {
			*output++ = uc;
		}
		else {
			if (is_high_surrogate(uc) && input < end && is_low_surrogate(*input))
				*output++ = surrogate_to_utf32(uc, *input++);
			else
				*output++ = 0; //ERROR
		}
	}
}


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

void convertUTF16ToUTF8(const WCHAR_T* src, int srcLen, string& output){

     utf8::utf16to8(src, src+srcLen, std::back_inserter(output));
}
