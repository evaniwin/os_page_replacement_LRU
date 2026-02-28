#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int lru_page_replacement(uint8_t *page_refrence, unsigned int page_refrence_len, uint8_t no_of_frames,uint16_t **frame_history, uint8_t **pagefaults);
uint8_t max(uint16_t *array, uint8_t array_len);
int find(uint16_t *array, uint8_t array_len, uint8_t target, uint16_t *indexfound);

int test_lru(void)
{
	uint8_t page_refrence[] = { 1, 2, 3, 1, 3, 2, 5, 8, 2 };
	unsigned int page_refrence_len = sizeof(page_refrence) / sizeof(uint8_t);
	uint8_t no_of_frames = 4;
	uint8_t *pagefaults = NULL;
	uint16_t *page_history = NULL;

	lru_page_replacement(page_refrence, page_refrence_len, no_of_frames, &page_history,&pagefaults);
	free(pagefaults);
	free(page_history);

	return 0;
}

int main(void)
{
	test_lru();
	return 0;
}

uint8_t max(uint16_t *array, uint8_t array_len)
{
	uint8_t max_index = 0;
	for (uint8_t i = 0; i < array_len; i++) {
		if (array[max_index] < array[i]) {
			max_index = i;
		}
	}
	return max_index;
}

int find(uint16_t *array, uint8_t array_len, uint8_t target, uint16_t *indexfound)
{
	for (uint8_t i = 0; i < array_len; i++) {
		if (array[i] == target) {
			*indexfound = i;
			return 1;
		}
	}
	return 0;
}

int lru_page_replacement(uint8_t *page_refrence, unsigned int page_refrence_len, uint8_t no_of_frames,uint16_t **frame_history, uint8_t **pagefaults)
{
	*frame_history = (uint16_t *)malloc(sizeof(uint16_t) * page_refrence_len * no_of_frames);
	if (*frame_history == NULL) {
		perror("Menory Alocation Failed");
		return -1;
	}
	uint16_t *frame_usage = (uint16_t *)malloc(sizeof(uint16_t) * no_of_frames);
	if (frame_usage == NULL) {
		perror("Menory Alocation Failed");
		return -1;
	}
	*pagefaults = (uint8_t *)malloc(sizeof(uint8_t) * page_refrence_len);
	if (*pagefaults == NULL) {
		perror("Menory Alocation Failed");
		free(frame_usage);
		return -1;
	}
	for (uint8_t i = 0; i < no_of_frames; i++) {
		frame_usage[i] = 1;
		(*frame_history)[i] = 0;
	}
	uint16_t *prev_frame = *frame_history;
	// lru
	for (unsigned int i = 0; i < page_refrence_len; i++) {
		uint16_t *next_frame = (*frame_history) + i * no_of_frames;
		// copy previous frame to next frame
		for (uint8_t j = 0; j < no_of_frames; j++) {
			next_frame[j] = prev_frame[j];
		}
		uint16_t hitfound;
		if (find(prev_frame, no_of_frames, page_refrence[i], &hitfound)) {
			frame_usage[hitfound] = 0;
			(*pagefaults)[i] = 0;
		} else {
			// Replace Oldest Refrence in frame
			uint8_t oldest = max(frame_usage, no_of_frames);
			frame_usage[oldest] = 0;
			next_frame[oldest] = page_refrence[i];
			(*pagefaults)[i] = 1;
		}

		//Incriment usage by one
		for (uint8_t j = 0; j < no_of_frames; j++) {
			frame_usage[j] = frame_usage[j] + 1;
		}
		prev_frame = next_frame;
	}
	for (int j = 0; j < no_of_frames; j++) {
		for (int i = 0; i < page_refrence_len; i++) {
			printf("%d ",(*frame_history)[i*no_of_frames+j]);
		}
		printf("\n");
	}
	free(frame_usage);
	return 0;
}
