Worst solution:
Since we always want to collapse a whole sub-tree at once, then we will always start from the leaves of the tree
There is a maximum of N/2 leaves, each total collapse can be done simply with DFS, so O(N)
In total this is O(N^2) time O(N) space

Different thought
Start at a node, when calculating costs in the left subtree, calculate as we have the right subtree saved
Do the same for the right subtree => Every layer deeper is just +1, apart from the lowest layer
Obviously works for base example, but what about asymmetrical example