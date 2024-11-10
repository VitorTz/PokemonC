#include "mstring.h"


void string_init(string_t* str) {
	str->capacity = 8;
	str->data = (char*) malloc(sizeof(char) * str->capacity);
	str->size = 1;
	*str->data = '\0';
}


void string_close(string_t* str) {
	free(str->data);
}


void string_append(string_t* str, const char* s) {
	const size_t str_size = strlen(s);
	if (str->size + str_size + 1 >= str->capacity) {
		void* tmp = realloc(str->data, str->capacity + str_size + 1);
		if (tmp != NULL) {
			str->data = tmp;
			str->capacity = str->capacity + str_size + 1;
		}
	}
	str->size--;
	char c;
	while ((c = *s++)) {
		*(str->data + str->size++) = c;
	}
	*(str->data + str->size) = '\0';
}


const char* string_get(string_t* str) {
	return (const char*)str->data;
}


void string_clear(string_t* str) {
	str->size = 1;
	*str->data = '\0';
}


size_t string_lenght(string_t* str) {
	return str->size - 1;
}