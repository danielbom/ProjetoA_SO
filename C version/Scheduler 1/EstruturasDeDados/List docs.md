### List

```c
/* CONSTRUTOR E DESTRUTOR */
List new_List(size_t size);
List array_to_List(void array, int length_array, size_t size);
void delete_List(List self);

/* FUNCOES DE BUSCA */
void index_List(List self, int pos);
index_no_List(List self, int pos);

bool contains_List(List self, void elem, cmp);
search_no_List(List self, void elem, cmp)(const void , const void ));

void max_List(List self, int (cmp)(const void , const void ));      
void min_List(List self, int (cmp)(const void , const void ));      
max_no_List(List self, int (cmp)(const void , const void )); 
min_no_List(List self, int (cmp)(const void , const void )); 

/* FUNCOES DE INSERCAO */
push_no_List(List self, void elem, pos); 
bool push_back_List(List self, void elem);               
bool push_front_List(List self, void elem);              

bool insert_List(List self, void elem, int pos); 

bool update_List(List dest, const List font);

/* FUNCOES DE REMOCAO */
pop_in_List(List self, pos); 
pop_back_no_List(List self);         
pop_front_no_List(List self);        
bool pop_back_List(List self);               
bool pop_front_List(List self);              
void pop_back_dado_List(List self);         
void pop_front_dado_List(List self);        

bool remove_List(List self, void elem, int (cmp)(const void , const void )); 
bool pop_List(List self, int pos);                                               
void remove_if_List(List self, bool (condicao)(void ));                        

void clear_List(List self); 

/* FUNCOES AUXILIARES */
void copy_List(List dest, const List fonte);                             
void swap_List(List L1, List L2);                                        
void print_List(List self, void (print)(const void ));                  
bool empyt_List(List self);                                               
void unique_List(List self, int (cmp)(const void , const void ));      
bool is_sorted_List(List self, int (cmp)(const void , const void ));   
bool is_reversed_List(List self, int (cmp)(const void , const void )); 
void reverse_List(List self);                                             
void List_to_array(List self);                                           
bool equals_List(const List a, const List b);

double sum_List(List self, double (cast)(const void ));  
double mult_List(List self, double (cast)(const void )); 

/* ITERADORES */
begin_List(const List self);  
last_List(const List self);   
end_List(const List self);    
void next_iter_List(no);      
rbegin_List(const List self); 
rlast_List(const List self);  
rend_List(const List self);   
void next_riter_List(no);     

/* FUNCOES DE ORDENACAO */
void sort_List(List self, int (cmp)(const void , const void ));                                            
void _quick_sort_List(List self, inicio, fim, int (cmp)(const void , const void )); 
_partition_List(inicio, fim, int (cmp)(const void , const void ));           
_partition_List2(inicio, fim, int (cmp)(const void , const void ));
```