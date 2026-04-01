#include <stdio.h>
#include <stdlib.h>

// Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Queue structure
struct QNode {
    struct Node* node;
    int hd;
};

struct Queue {
    int front, rear;
    struct QNode arr[100];
};

void enqueue(struct Queue* q, struct Node* node, int hd) {
    q->arr[++q->rear].node = node;
    q->arr[q->rear].hd = hd;
}

struct QNode dequeue(struct Queue* q) {
    return q->arr[q->front++];
}

// Vertical Order Traversal
void verticalOrder(struct Node* root) {
    if (!root) return;

    struct Queue q;
    q.front = 0;
    q.rear = -1;

    // Map using array (range assumed -50 to +50)
    int map[101][100];
    int count[101] = {0};

    enqueue(&q, root, 50);

    while (q.front <= q.rear) {
        struct QNode temp = dequeue(&q);
        struct Node* curr = temp.node;
        int hd = temp.hd;

        map[hd][count[hd]++] = curr->data;

        if (curr->left)
            enqueue(&q, curr->left, hd - 1);

        if (curr->right)
            enqueue(&q, curr->right, hd + 1);
    }

    // Print result
    for (int i = 0; i < 101; i++) {
        if (count[i] > 0) {
            for (int j = 0; j < count[i]; j++) {
                printf("%d ", map[i][j]);
            }
            printf("\n");
        }
    }
}

// Build tree from level order
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = newNode(arr[0]);

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;
    int i = 1;

    while (i < n) {
        struct Node* curr = queue[front++];

        if (arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;

        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }

    return root;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(arr, n);

    verticalOrder(root);

    return 0;
}