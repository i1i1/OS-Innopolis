#include <stdio.h>

typedef struct list {
	struct list *next;
	int val;
} list;


void
insert_node(list *a, list *b)
{
	a->next = b;
}

void
delete_node(list *a, list *b)
{
	while (a) {
		if (a->next != b) {
			a = a->next;
			continue;
		}
		a->next = b ? b->next : NULL;
		return;
	}
}

void
print_list(list *a)
{
	while (a) {
		printf("%d ", a->val);
		a = a->next;
	}
	printf("\n");
}

int
main(void)
{
	list a, b, c;

	a.val = 3;
	b.val = 2;
	c.val = 1;

	insert_node(&a, &b);
	insert_node(&b, &c);
	insert_node(&c, NULL);

	print_list(&a);
	delete_node(&a, &b);
	print_list(&a);

	return 0;
}
