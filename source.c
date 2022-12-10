#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef enum colors{
	RED,
	BLACK
}node_color;

typedef struct node* node_pt;
typedef struct node {
  int key;
	node_color color;
	node_pt right;
	node_pt left;
	node_pt dad;
}node;

node_pt external;

int generate_key() {
  int key = 0;
  key = (rand() % 100000);
  return key;
}

void node_counter(node_pt pt, int* amount){
	if(pt != external){
		(*amount)++;
		node_counter(pt->right, amount);
		node_counter(pt->left, amount);
	}
}

void pre_order(node_pt pt){
	if(pt != external){
		printf("%-2d, ", pt->key);
		pre_order(pt->right);
		pre_order(pt->left);
	}
}

void pre_order_color(node_pt pt){
	if(pt != external){
		if(pt->color == 0)
		  printf("%-2c, ", 'R');
		else
		  printf("%-2c, ", 'N');

		pre_order_color(pt->right);
		pre_order_color(pt->left);
	}
}

void start_node(){
	external = (node*)malloc(sizeof(node));
	external->right = external->left = external;
	external->dad = external;
	external->color = BLACK;
	external->key = -1;
}

void create_node(node_pt* z, int ch){
	(*z) = malloc(sizeof(node));
	(*z)->key = ch;
}

node_pt successor(node_pt z){
	node_pt s = z;

	while(s->left != external)
		s = s->left;

	return s;
}

void move_dad(node_pt u, node_pt v, node_pt* root_pt){
	if(u->dad == external)
		(*root_pt) = v;
	else
		if(u == u->dad->left)
			u->dad->left = v;
		else
			u->dad->right = v;

	v->dad = u->dad;
}

void left_rotation(node_pt pt, node_pt* root_pt){
	node_pt y = pt->right;
	pt->right = y->left;
	if (y->left != external)
    y->left->dad = pt;

	move_dad(pt, y, &(*root_pt));
	y->left = pt;
	pt->dad = y;
}


void right_rotation(node_pt pt, node_pt* root_pt){
	node_pt y = pt->left;
	pt->left = y->right;
	if (y->right != external)
    y->right->dad = pt;

	move_dad(pt, y, &(*root_pt));
	y->right = pt;
	pt->dad = y;
}


void route(node_pt z, node_pt* root_pt){
	node_pt y;
	while(z->dad->color == RED){
		if(z->dad == z->dad->dad->left){
			y = z->dad->dad->right;
			if(y->color == RED){
				z->dad->color = y->color = BLACK;
				z->dad->dad->color = RED;
				z = z->dad->dad;
			}else{
				if(z == z->dad->right){
					z = z->dad;
					left_rotation(z, &(*root_pt));
				}
				z->dad->color = BLACK;
				z->dad->dad->color = RED; 
				right_rotation(z->dad->dad, &(*root_pt));
			}
		}else{
			y = z->dad->dad->left;
			if(y->color == RED){
				z->dad->color = y->color = BLACK;
				z->dad->dad->color = RED;
				z = z->dad->dad;
			}else{
				if(z == z->dad->left){
					z = z->dad;
					right_rotation(z, &(*root_pt));
				}
				z->dad->color = BLACK;
				z->dad->dad->color = RED;
				left_rotation(z->dad->dad, &(*root_pt));
			}
		}
	}
	(*root_pt)->color = BLACK;
}

int insert(int ch, node_pt* root_pt){
	node_pt y = external; node_pt pt = (*root_pt);
	node_pt z;

	create_node(&z, ch);

	while(pt != external){ //buscar nó.
		y = pt;
		if(z->key == pt->key){
			y = NULL;
			pt = external;
			return 1;
		}else{
			if(z->key < pt->key){
				pt = pt->left;
			}else{
				pt = pt->right;
			}
		}
	}

	if(y != NULL){
		z->dad = y;

		if(y == external){
			(*root_pt) = z;
		}else{
			if(z->key < y->key){
				y->left = z;
			}else{
				y->right = z;
			}
		}
		z->left = z->right = external;
		z->color = RED;
		route(z, &(*root_pt));
	}
	return 0;
}

void Rotaremove_red_black(node_pt x, node_pt* root_pt){
	node_pt w;

	while(x != (*root_pt) && x->color != RED){
		if(x == x->dad->left){
			w = x->dad->right;
			if(w->color == RED){
				x->dad->color = RED; w->color = BLACK;
				left_rotation(x->dad, &(*root_pt));
				w = x->dad->right;
			}
			if(w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				x = x->dad;
			}else{
				if(w->right->color == BLACK){
					w->left->color = BLACK; w->color = RED;
					right_rotation(w, &(*root_pt));
					w = x->dad->right;
				}
				w->color = x->dad->color;
				x->dad->color = BLACK;
				w->right->color = BLACK;
				left_rotation(x->dad, &(*root_pt));
				x = (*root_pt);
			}
		}else{
			w = x->dad->left;
			if(w->color == RED){
				x->dad->color = RED; w->color = BLACK;
				right_rotation(x->dad, &(*root_pt));
				w = x->dad->right;
			}

			if(w->right->color == BLACK && w->left->color == BLACK && w != external){
				w->color = RED;
				x = x->dad;
			}else{

      if(w != external){ 
				if(w->left->color == BLACK){
					w->right->color = BLACK; w->color = RED;
					left_rotation(w, &(*root_pt));
					w = x->dad->left;
				}
				w->color = x->dad->color;
				x->dad->color = BLACK;
				w->left->color = BLACK;
				right_rotation(x->dad, &(*root_pt));
				x = (*root_pt);
			}
    }
  }  
}
	x->color = BLACK;
}

void remove_red_black(int ch, node_pt* root_pt){

	node_pt z, pt = (*root_pt), y;
	create_node(&z, ch);

	while(pt != external){ //buscando o nó.
		y = pt;
		if(z->key == pt->key){
			y = pt;
			pt = external;
		}else{
			if(z->key < pt->key){
				pt = pt->left;
			}else{
				pt = pt->right;
			}
		}
	}
	z = y;

	y = z;
	node_pt x;
	node_color original_color = y->color;
	pt = (*root_pt);

	if(z->left == external){
		x = z->right;
		move_dad(z, z->right, &(*root_pt));
	}else{
		if(z->right == external){
			x = z->left;
			move_dad(z, z->left, &(*root_pt));
		}else{
			y = successor(z->right); original_color = y->color;
			x = y->right;

			if(y->dad == z){
				x->dad = y;
			}else{
				move_dad(y, x, &(*root_pt));
				y->right = z->right;
				y->right->dad = y;
			}

			move_dad(z, y, &(*root_pt));
			y->left = z->left;
			y->left->dad = y;
			y->color = z->color;
		}
	}

	if(original_color == BLACK){
		Rotaremove_red_black(x, &(*root_pt));
	}
}

int check_tree(node_pt no){

	if(no == NULL || no == external)
		return 0;

	int left = check_tree(no->left);
	int right = check_tree(no->right);
	int x   = no->color == BLACK ? 1 : 0;

	if(left == -1 || right == -1 || left != right)
		return -1;
	else
		return left+x;

}

int main(){

	start_node();
	node_pt raiz;
	raiz = external;
	srand(time(NULL));
	int qtd=0;

	int vet[10000];
		for(int i = 0; i < 10000; i++){ //inserindo 10000 nós.
			vet[i] = generate_key();
			if(insert(vet[i], &raiz) == 1){
				i--;		
			}
		}

		//verificando a quantidade de nós e se é RED negra
		qtd = 0;
		node_counter(raiz, &qtd);
		printf("\nQtd = %d\n\n", qtd);

		if(check_tree(raiz) == -1)
			printf("Nao eh rubro negra\n\n");
		else
			printf("Eh rubro negra\n\n");

	for(int i = 0; i < 1000; i++){ //remover 1000 nós.
		remove_red_black(vet[i] , &raiz);
	}

	//verificando a quantidade de nós e se é rubro negra
	qtd = 0;
	node_counter(raiz, &qtd);
	printf("\nQtd = %d\n\n", qtd);

	if(check_tree(raiz) == -1)
		printf("Remover Nao eh rubro negra\n\n");
	else
		printf("Remover eh rubro negra\n\n");

	return 0;
}