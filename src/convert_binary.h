
inline void convert_binary( uint64_t bit, int *indices ) {
	int offset;
	int i = 0;

	while( bit ) {
		offset = __builtin_clzll(bit);
		indices[i] = 63-offset;
		BIT_FLIP(bit,63-offset);
		i++;
	}

	return;
}
