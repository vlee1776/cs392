// Compute the sum of a file full of binary 16-bit integer data,
// parallel version.

// TODO: parallelize this program!

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

struct mmap_region {
	int fd;
	void *addr;
	size_t size;
};

size_t get_file_size(const char *filename);
void map_file_region(const char *filename, size_t size, struct mmap_region *region);
void unmap_file_region(struct mmap_region *region);

struct info{
	uint64_t total;
	uint16_t length;
	uint16_t* array;
};

void* half(struct info* first){
	uint16_t num_elements=first->length;
	uint16_t* data=first->array;
	uint64_t sum=0ULL; 
	for (uint16_t i = num_elements/2; i < num_elements; i++) {
		sum += data[i];
	}
	first->total=sum;
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	uint16_t *data;
	size_t i, size, num_elements;
	uint64_t sum;
	struct mmap_region region;

	if (argc != 2) {
		fprintf(stderr, "Usage: sumu16 <input file>\n");
		exit(1);
	}

	// Find out how large the file is.
	size = get_file_size(argv[1]);
	printf("File is %lu bytes in size\n", size);

	// Each element (datum) is 16 bits.
	// Find out how many elements there are overall.
	num_elements = size / sizeof(uint16_t);

	// Map the file data into memory
	map_file_region(argv[1], size, &region);
	data = region.addr;
	
	struct info* first=(struct info*)malloc(sizeof(struct info));
	first->array=data;
	first->total=0;
	first->length=num_elements;
	pthread_t thread;
	pthread_create(&thread,NULL, (void*)half, (void*)first);
	pthread_join(thread,NULL); 
	// Compute the sum
	uint64_t sum2=first->total;
	sum = 0ULL;
	for (i = 0; i < num_elements/2; i++) {
		sum += data[i];
	}
	sum+=sum2;
	printf("Sum is %lu\n", sum);

	unmap_file_region(&region);

	return 0;
}

size_t get_file_size(const char *filename)
{
	struct stat file_info;

	if (stat(filename, &file_info) < 0) {
		fprintf(stderr, "Could not stat %s: %s\n", filename, strerror(errno));
		exit(1);
	}
	return (size_t)file_info.st_size;
}

void map_file_region(const char *filename, size_t size, struct mmap_region *region)
{
	region->size = size;

	// Open the file
	region->fd = open(filename, O_RDONLY);
	if (region->fd < 0) {
		fprintf(stderr, "Could not open %s: %s\n", filename, strerror(errno));
		exit(1);
	}

	// Map the file into memory.
	region->addr = mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, region->fd, (off_t)0);
	if (region->addr == MAP_FAILED) {
		fprintf(stderr, "Could not map %s: %s\n", filename, strerror(errno));
		exit(1);
	}
}

void unmap_file_region(struct mmap_region *region)
{
	munmap(region->addr, region->size);
	close(region->fd);
}


