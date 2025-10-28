CC = g++
CFLAGS = -Wall -g
BinTree_OBJS = BinTree.o stackTool.o queueLink.o avl.o
TestAVL_OBJS = test_avl.o avl.o
# 分别编译每个源文件
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 链接所有目标文件
BinTree: $(BinTree_OBJS)
	$(CC) -o $@ $(BinTree_OBJS)
testAVL: $(TestAVL_OBJS)
	$(CC) -o $@ $(TestAVL_OBJS)
.PHONY: clean
clean: 
	rm -f $(BinTree_OBJS) BinTree
	rm -f $(TestAVL_OBJS) TestAVL
	rm -f stack stack2 test_queue testAVL hashMap BinTree_Array
