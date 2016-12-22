CXX=g++
CFLAGS= -O3 -g -Wall `pkg-config --cflags opencv`
LDLIBS= `pkg-config --libs opencv`
SUFFIXES= .cpp .o
OBJS= read_save_img_data.o
read_save_img_data: $(OBJS)
	$(CXX) -O3 -o read_save_img_data $(OBJS) $(LDLIBS)
.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@
clean:
	rm read_save_img_data read_save_img_data.o
