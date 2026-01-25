#include <gtest/gtest.h>

#define N 10

int sz[N];  // sz array to track the size of each tree

bool connected__quick_find(const int* id, int p, int q) {
    return id[p] == id[q];
}

void union__quick_find(int* id, int p, int q) {
    int pid = id[p];
    int qid = id[q];
    for (int i = 0; i < N; ++i) {
        if (id[i] == pid) id[i] = qid;
    }
}

int root__quick_union(const int* id, int i) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

void union__quick_union(int* id, int p, int q) {
    int root_p = root__quick_union(id, p);
    int root_q = root__quick_union(id, q);
    id[root_p] = root_q;
}

int root__quick_union_path_compression(int* id, int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}

void union__weighted_quick_union(int* id, int p, int q) {
    int root_p = root__quick_union_path_compression(id, p);
    int root_q = root__quick_union_path_compression(id, q);

    if (root_p == root_q) return;

    if (sz[root_p] < sz[root_q]) {
        id[root_p] = root_q;
        sz[root_q] += sz[root_p];
    } else {
        id[root_q] = root_p;
        sz[root_p] += sz[root_q];
    }
}

class QuickUnionTest : public ::testing::Test {
protected:
    int id[N];

    void SetUp() override {
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    void TearDown() override {
    }
};

TEST_F(QuickUnionTest, Connected__QuickFind) {
    id[3] = id[4] = 1;
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    EXPECT_FALSE(connected__quick_find(id, 3, 5));
}

TEST_F(QuickUnionTest, Union__QuickFind) {
    union__quick_find(id, 0, 1);
    EXPECT_TRUE(connected__quick_find(id, 0, 1));
    EXPECT_EQ(id[0], id[1]);

    union__quick_find(id, 2, 3);
    EXPECT_TRUE(connected__quick_find(id, 2, 3));

    union__quick_find(id, 1, 2);
    EXPECT_TRUE(connected__quick_find(id, 0, 3));

    int common_id = id[3];
    EXPECT_EQ(id[0], common_id);
    EXPECT_EQ(id[1], common_id);
    EXPECT_EQ(id[2], common_id);
}

TEST_F(QuickUnionTest, Root__QuickUnion) {
    id[3] = 4;
    id[4] = 9;

    EXPECT_EQ(root__quick_union(id, 3), 9);
    EXPECT_EQ(root__quick_union(id, 4), 9);
    EXPECT_EQ(root__quick_union(id, 9), 9);
}

TEST_F(QuickUnionTest, Connected__QuickUnion) {
    id[0] = 1;
    
    EXPECT_EQ(root__quick_union(id, 0), root__quick_union(id, 1));
    
    EXPECT_NE(root__quick_union(id, 0), root__quick_union(id, 2));
}

TEST_F(QuickUnionTest, Union__QuickUnion) {
    union__quick_union(id, 3, 4);

    EXPECT_EQ(id[3], 4);
    EXPECT_EQ(root__quick_union(id, 3), 4);
    
    union__quick_union(id, 4, 9);
    
    EXPECT_EQ(root__quick_union(id, 3), 9);
}

TEST_F(QuickUnionTest, Union__WeightedQuickUnion) {

    sz[0] = 1;
    sz[1] = 2;
    
    union__weighted_quick_union(id, 0, 1);
    
    EXPECT_EQ(id[0], 1);
    EXPECT_EQ(id[1], 1);
    
    EXPECT_EQ(sz[1], 3);
    
    union__weighted_quick_union(id, 1, 2);
    
    EXPECT_EQ(id[2], 1);
    EXPECT_EQ(sz[1], 4);
}

TEST_F(QuickUnionTest, Root__QuickUnionPathCompression) {
    id[0] = 1;
    id[1] = 2;
    
    int root = root__quick_union_path_compression(id, 0);
    
    EXPECT_EQ(root, 2);
    
    EXPECT_EQ(id[0], 2);
}