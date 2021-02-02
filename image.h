
#ifndef IMAGE_H_
#define IMAGE_H_

class Image {
public:
	int width, height;
	unsigned char *data;
	
	~Image();
	Image();
	Image(const char*);
	void init(const char*);

	static unsigned char* buildAlphaData(Image*);
};

#endif
