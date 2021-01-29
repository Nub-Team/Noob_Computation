//Author by : Nub-T

class UnionFind{
	private int[] parent, size;
	private int components;
		 
	public UnionFind(int n){
		components = n;
		parent = new int[n];
		size = new int[n];
		for(int i=0; i<n; i++){
			parent[i] = i;
			size[i] = 1;
		}
	}

	private int root(int p){
		while(p != parent[p]){
			parent[p] = parent[parent[p]];
			p = parent[p];
		}
		return p;
	}

	public void union(int p, int q){
		int rootP = root(p);
		int rootQ = root(q);
		if(rootP != rootQ){
			if(size[rootP] < size[rootQ]){
				parent[rootP] = rootQ;
				size[rootQ] = size[rootQ] + size[rootP];
			}else{
				parent[rootQ] = rootP;
				size[rootP] = size[rootP] + size[rootQ];
			}
			components--;
		}
	}
	public boolean connected(int p, int q){
		return root(p) == root(q);
	}

	public int getComponents(){
		return components;
	}
}

class Main {
	public static void main(String[] args){		
		UnionFind uf = new UnionFind(5);
		uf.union(0, 2);
		uf.union(1, 0);
		uf.union(3, 4);
		int comp = uf.getComponents();
	
		boolean connected = uf.connected(1, 2);
	}
}
