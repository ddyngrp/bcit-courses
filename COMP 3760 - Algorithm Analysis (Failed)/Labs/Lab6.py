root <- tree.root()
lChild <- node.left()
rChild <- node.right()
value <- node.value()

Queue<int> q;
int[] heap;

int[0] = root; # this is always first anyhow.

while (root != null)
	if (root.lChild != null)
		q.add(root.lChild.value)

	if (root.rChild != null)
		q.add(root.rChild.value)


	if (root.lChild = null && root.rChild = null )
		root = null;

	
	if (root.lChild != null)
		root <- lChild

	else if (root.rChild != null)
		root <- rChild

	else
		root <- tree.root.rChild

for i = 1 to q.length do
	heap[i] = q.remove()
