#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int optimal_page_replacement(uint8_t *page_refrence, unsigned int page_refrence_len, uint8_t no_of_frames, uint16_t **frame_history, uint8_t **pagefaults);
int farthest_num_in_frame(uint16_t *frame,uint8_t no_of_frames,uint8_t *page_refrence, unsigned int page_refrence_len);
int lru_page_replacement(uint8_t *page_refrence, unsigned int page_refrence_len, uint8_t no_of_frames, uint16_t **frame_history, uint8_t **pagefaults);
uint8_t max(uint16_t *array, uint8_t array_len);
int find(uint16_t *array, uint8_t array_len, uint8_t target, uint16_t *indexfound);

int main(void)
{
	int ref_len;
	int frame_len;

	printf("\nEnter the length of the refrence String\n> ");
	scanf("%d",&ref_len);
	printf("\nEnter the size of the frame\n> ");
	scanf("%d",&frame_len);

	if(frame_len > 7 || frame_len < 1){
		printf("Number of frames Should be between 1 and 7\n");
		return -1;
	}

	FILE *fd = fopen("/dev/random","r");
	if(fd == NULL){
		perror("Failed to open file");
		return -1;
	}

	unsigned int random_seed;
	fread(&random_seed,sizeof(unsigned int),1,fd);
	fclose(fd);
	srand(random_seed);

	uint8_t *reference_string = (uint8_t *)malloc(sizeof(int)*ref_len);
	if(reference_string == NULL){
		perror("Failed to Allocate Memory");
		return -1;
	}

	printf("Generated Reference String:\n");
	for(int i = 0;i<ref_len;i++){
		reference_string[i] = (rand()%10);
		printf("%u ",reference_string[i]);
	}
	printf("\n");

	uint16_t *lru_framehistory = NULL;
	uint8_t *lru_pagefaults = NULL;
	lru_page_replacement(reference_string, ref_len, frame_len,&lru_framehistory, &lru_pagefaults);

	uint16_t *optimal_framehistory = NULL;
	uint8_t *optimal_pagefaults = NULL;
	optimal_page_replacement(reference_string, ref_len, frame_len,&optimal_framehistory, &optimal_pagefaults);

	free(optimal_framehistory);
	free(optimal_pagefaults);
	free(lru_framehistory);
	free(lru_pagefaults);
	free(reference_string);

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
int farthest_num_in_frame(uint16_t *frame,uint8_t no_of_frames,uint8_t *page_refrence, unsigned int page_refrence_len){
	
	return 0;
}
int optimal_page_replacement(uint8_t *page_refrence, unsigned int page_refrence_len, uint8_t no_of_frames, uint16_t **frame_history, uint8_t **pagefaults)
{
	*frame_history = (uint16_t *)malloc(sizeof(uint16_t) * page_refrence_len * no_of_frames);
	if (*frame_history == NULL) {
		perror("Menory Alocation Failed");
		return -1;
	}
	*pagefaults = (uint8_t *)malloc(sizeof(uint8_t) * page_refrence_len);
	if (*pagefaults == NULL) {
		perror("Menory Alocation Failed");
		return -1;
	}
	for (uint8_t i = 0; i < no_of_frames; i++) {
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
			(*pagefaults)[i] = 0;
		} else {
			// Replace farthest Refrence in frame
			uint8_t farthest = farthest_num_in_frame(prev_frame, no_of_frames, page_refrence, page_refrence_len);
			next_frame[farthest] = page_refrence[i];
			(*pagefaults)[i] = 1;
		}

		prev_frame = next_frame;
	}
	for (int j = 0; j < no_of_frames; j++) {
		for (int i = 0; i < page_refrence_len; i++) {
			printf("%d ", (*frame_history)[i * no_of_frames + j]);
		}
		printf("\n");
	}
	return 0;
}

int lru_page_replacement(uint8_t *page_refrence, unsigned int page_refrence_len, uint8_t no_of_frames, uint16_t **frame_history, uint8_t **pagefaults)
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
		(*frame_history)[i] = 10;
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
			printf("%d ", (*frame_history)[i * no_of_frames + j]);
		}
		printf("\n");
	}
	free(frame_usage);
	return 0;
}
