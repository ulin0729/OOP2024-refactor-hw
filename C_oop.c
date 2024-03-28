#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next, *prev;
} Node;

typedef struct deque {
    struct deque_type *vdeque;
    Node *head, *tail;
    int size;
} deque;

void construct(deque *self);
void destruct(deque *self);
deque *new();
void push_back(deque *self, Node *node);
void push_front(deque *self, Node *node);
Node *pop_back(deque *self);
void print(deque *self);
void moveto(deque *self, deque *dst);
void shuffle(deque *self, deque *dst);
void print(deque *self);

struct deque_type {
    void (*construct)(deque *self);
    void (*destruct)(deque *self);
    deque *(*new)();
    void (*push_back)(deque *self, Node *node);
    void (*push_front)(deque *self, Node *node);
    Node *(*pop_back)(deque *self);
    void (*moveto)(deque *self, deque *dst);
    void (*shuffle)(deque *self, deque *dst);
    void (*print)(deque *self);
} Deque = {
    .construct = &construct,
    .destruct = &destruct,
    .new = &new,
    .push_back = &push_back,
    .push_front = &push_front,
    .pop_back = &pop_back,
    .print = &print,
    .moveto = &moveto,
    .shuffle = &shuffle,
};

void construct(deque *self) {
    self->vdeque = &Deque;
    self->head = NULL;
    self->tail = NULL;
    self->size = 0;
}

void destruct(deque *self) {
    while (self->size > 0) {
        Node *node = self->vdeque->pop_back(self);
        free(node);
    }
    free(self);
}

deque *new() {
    deque *self = malloc(sizeof(deque));
    return self;
}

void push_back(deque *self, Node *node) {
    node->next = NULL;
    node->prev = self->tail;
    if (self->size == 0) {
        self->head = node;
        self->tail = node;
    } else {
        self->tail->next = node;
        self->tail = node;
    }
    self->size++;
}

void push_front(deque *self, Node *node) {
    node->prev = NULL;
    node->next = self->head;
    if (self->size == 0) {
        self->head = node;
        self->tail = node;
    } else {
        self->head->prev = node;
        self->head = node;
    }
    self->size++;
}

Node *pop_back(deque *self) {
    if (self->size == 0) return NULL;
    Node *node = self->tail;
    self->tail = self->tail->prev;
    if (self->tail)
        self->tail->next = NULL;
    else
        self->head = NULL;
    self->size--;
    return node;
}

void moveto(deque *self, deque *dst) {
    if (self->size == 0) return;
    self->head->prev = dst->tail;
    if (dst->size > 0)
        dst->tail->next = self->head;
    else {
        dst->head = self->head;
    }
    dst->tail = self->tail;
    dst->size += self->size;
    self->head = NULL;
    self->tail = NULL;
    self->size = 0;
    return;
}

void shuffle(deque *self, deque *dst) {
    deque *tmp = Deque.new();
    Deque.construct(tmp);
    while (self->size > 0 && dst->size > 0) {
        tmp->vdeque->push_front(tmp, self->vdeque->pop_back(self));
        tmp->vdeque->push_front(tmp, dst->vdeque->pop_back(dst));
    }
    while (self->size > 0) {
        tmp->vdeque->moveto(tmp, self);
        self->vdeque->moveto(self, tmp);
    }
    tmp->vdeque->moveto(tmp, dst);
    Deque.destruct(tmp);
    return;
}

void print(deque *self) {
    printf("%d ", self->size);
    Node *node = self->tail;
    while (node) {
        printf("%d ", node->val);
        node = node->prev;
    }
    printf("\n");
    return;
}

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    deque **decks = (deque **)malloc(sizeof(deque *) * (N + 1));
    for (int i = 1; i <= N; i++) {
        decks[i] = Deque.new();
        Deque.construct(decks[i]);
    }
    int instruction, a, b;
    for (int i = 0; i < M; i++) {
        scanf("%d", &instruction);
        switch (instruction) {
            case 1: {
                scanf("%d %d", &a, &b);
                Node *node = (Node *)malloc(sizeof(Node));
                node->val = b;
                decks[a]->vdeque->push_back(decks[a], node);
                decks[a]->tail->val = b;
                break;
            }
            case 2: {
                scanf("%d", &a);
                Node *node = decks[a]->vdeque->pop_back(decks[a]);
                free(node);
                break;
            }
            case 3: {
                scanf("%d %d", &a, &b);
                decks[a]->vdeque->moveto(decks[a], decks[b]);
                break;
            }
            case 4: {
                scanf("%d %d", &a, &b);
                decks[a]->vdeque->shuffle(decks[a], decks[b]);
                break;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        decks[i]->vdeque->print(decks[i]);
        Deque.destruct(decks[i]);
    }
    return 0;
}