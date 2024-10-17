#pragma once



namespace gen
{

	namespace obj
	{

		struct data
		{
			float *v;
			unsigned int vCount;
			unsigned int vDimension;
			float *vt;
			unsigned int vtCount;
			unsigned int vtDimension;
			float *vn;
			unsigned int vnCount;
			unsigned int vnDimension;
			unsigned short *f;
			unsigned int fCount;
			unsigned int fDimension;

			~data();
		};

		data readFile(const char*);
		void cleanup(data);

	}


	namespace image
	{

		struct data
		{
			int width;
			int height;
			int channelsCount;
			unsigned char *pixels;

			~data();
		};

		data readFile(const char*);
		void cleanup(data);

	}


}