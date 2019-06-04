/*!
 * Esta classe implementa o TAD Container Sequencial (aka sequencia, lista)
 * utilizando uma lista duplamente encadeada como estutura de dados.
 *
 */
#ifndef LLIST_H
#define LLIST_H

#include <iostream>
#include <exception>
#include <algorithm> 
#include <iterator>
#include <initializer_list>

/// Struct dos nodes
template<typename T>
struct node
{
    node * prev;
    T data;
    node * next;

    node(node * p = nullptr, T value=T(), node * n = nullptr)
    {
        prev = p;
        data = value;
        next = n;
    }

};



namespace sc 
{
    /// Classe que implementa um container sequencial com lista encadeada.
    template<typename T>
    class list
    {
        public:
            typedef unsigned long int size_type;

        /// Classe que implementa um iterator comum para a classe list.
        class iterator  
        {
            public:
                    typedef std::ptrdiff_t difference_type;
                    typedef node <T> value_type;
                    typedef node <T> * pointer;
                    typedef node <T> & reference;
                    typedef std::bidirectional_iterator_tag iterator_category;
            
            private:
                node <T> *ptr;

            public:
                iterator(node <T> *pt = nullptr) : ptr{pt}
                { /* empty */

                }

                iterator &operator=(const iterator &rhs)
                {
                    this->ptr = rhs.ptr;
                    return *this;
                }

                bool operator==(const iterator &it) const
                {
                    return this->ptr == it.ptr;
                }

                bool operator!=(const iterator &it) const
                {
                    return this->ptr != it.ptr;
                }

                T & operator*(void)
                {
                    return ptr->data;
                }

                T operator*(void) const
                {
                    return ptr->data;
                }

                iterator operator++(void)
                {
                    ptr = ptr->next;
                    return iterator(ptr);
                }

                iterator operator++(int) 
                {
                    iterator temp(ptr); 
                    ptr = ptr->next;
                    return temp;
                }

                iterator operator--(void)
                {
                    ptr = ptr->prev;
                    return iterator(ptr);
                }

                iterator operator--(int) 
                {
                    iterator temp(ptr); 
                    ptr = ptr->prev;
                    return temp;
                }

                node <T> * & getprev()
                {
                	return ptr->prev;
                }

                node <T> * & getnext()
                {
                	return ptr->next;
                }

        };

        /// Classe que implementa um iterator constante para a classe list.
        class const_iterator  
        {
            public:
                    typedef std::ptrdiff_t difference_type;
                    typedef node <T> value_type;
                    typedef node <T> * pointer;
                    typedef node <T> & reference;
                    typedef std::bidirectional_iterator_tag iterator_category;
            
            private:
                node <T> *ptr;

            public:
                const_iterator(node <T> *pt = nullptr) : ptr{pt}
                { /* empty */

                }

                const_iterator &operator=(const const_iterator &rhs)
                {
                    this->ptr = rhs.ptr;
                    return *this;
                }

                bool operator==(const const_iterator &it) const
                {
                    return this->ptr == it.ptr;
                }

                bool operator!=(const const_iterator &it) const
                {
                    return this->ptr != it.ptr;
                }


                T operator*(void) const
                {
                    return ptr->data;
                }

                const_iterator operator++(void)
                {
                    ptr = ptr->next;
                    return const_iterator(ptr);
                }

                const_iterator operator++(int) 
                {
                    const_iterator temp(ptr); 
                    ptr = ptr->next;
                    return temp;
                }

                const_iterator operator--(void)
                {
                    ptr = ptr->prev;
                    return const_iterator(ptr);
                }

                const_iterator operator--(int) 
                {
                    const_iterator temp(ptr); 
                    ptr = ptr->prev;
                    return temp;
                }

        };
        
        //=== private area
        private:
            node<T> * head;
            node<T> * tail;
            size_type list_size;
        
        //=== Public interface
        public:

            //=== Special members

            /// Contrutor default.
            list()
            {
                head = new node <T> ();
                tail = new node <T> ();
                head->prev = nullptr;
                head->next = tail;
                tail->prev = head;
                tail->next = nullptr;
                list_size = 0;
            }
            
            /// Construtor explicito.
            explicit list( size_type count )
            {
                head = new node <T> ();
                tail = new node <T> ();
                head->prev = nullptr;
                head->next = tail;
                tail->prev = head;
                tail->next = nullptr;

                for(size_t i = 0; i<count; i++)
                {
                    push_back(0);
                    //std::cout << temp->data + i << " ";
                }
                
                list_size = count;
            }

            /// Construtor a partir de um range.
            template< typename InputIt >
            list( InputIt first, InputIt last )
            {
            	int cont = 0;
            	head = new node <T> ();
                tail = new node <T> ();
                head->prev = nullptr;
                head->next = tail;
                tail->prev = head;
                tail->next = nullptr;
                while(first != last)
                {
                    push_back(*first);
                    first++;
                    cont++;
                }
                list_size = cont;
            } 
            
            /// Construtor cópia.
            list( const list& other )
            {
                head = new node <T> ();
                tail = new node <T> ();
                head->prev = nullptr;
                head->next = tail;
                tail->prev = head;
                tail->next = nullptr;
                auto temp = other.begin();
                while(temp != other.end())
                {
                    push_back((*temp));
                    temp++;
                }
                list_size = other.size();
            }

            /// Construtor a partir de uma lista inicializadora.
            list( std::initializer_list<T> ilist )
            {
                head = new node <T> ();
                tail = new node <T> ();
                head->prev = nullptr;
                head->next = tail;
                tail->prev = head;
                tail->next = nullptr;
                for(auto e : ilist)
                {
                    push_back(e);
                }
                list_size = ilist.size();
            }

            /// Destrutor default.
            ~list( )
            {
                clear();
                delete head;
                delete tail;
            }

            /// Operador de atribuição.
            list & operator=( const list& other )
            {
                auto temp = other.begin();
                int cont = 0;
                clear();
                while(temp != other.end())
                {
                    push_back((*temp));
                    temp++;
                    cont++;
                }
                list_size = cont;
                return *this;
            }

            /// Operador de atribuição a partir de lista inicializadora.
            list& operator=( std::initializer_list<T> ilist )
            {
                clear();
                for(auto e : ilist)
                {
                    push_back(e);
                }
                list_size = ilist.size();
                return *this;
            }

            //=== interface pública

            /// Retorna se a lista esta vazia.
            bool empty()
            {
            	return(list_size == 0);
            }

            /// Deleta todos os elementos da lista.
            void clear()
            {
                size_type siz = size();
                for(size_type i = 0; i<siz; i++)
                {
                    pop_front();
                }
                list_size = 0;
            }

            /// Retorna o tamanho da lista.
            size_type size() const
            {
                return list_size;
            }

            /// Insere um elemento no final da lista.
		    /*! 
			*    @param item O item a ser inserido na lista    */
            void push_back( const T & value ) // Prontinha mané
            {
                node<T> * temp = new node <T> ();
                node<T> * temp2;
                temp->prev = tail->prev;
                temp->data = value;
                temp->next = tail;
                temp2 = tail->prev;
                tail->prev = temp;
                temp2->next = temp;
                list_size++;

            }


            /// Insere um elemento no inicio da lista.
		    /*! 
			*    @param item O item a ser inserido na lista    */
            void push_front( const T & value ) // Protinha mané
            {
                node<T> * temp = new node <T> ();
                node<T> * temp2;
                temp->prev = head;
                temp->data = value;
                temp->next = head->next;
                temp2 = head->next;
                temp2->prev = temp;
                head->next = temp;
                list_size++;
            }

            /// Remove o último elemento da lista.
            void pop_back()
            {
                node<T> * temp;
                node<T> * temp2;
                temp = tail->prev;
                temp2 = temp;
                temp = temp->prev;
                temp->next = temp2->next;
                tail->prev = temp;
                list_size--;
                delete temp2;
            }

            /// Remove o primeiro elemento da lista.
            void pop_front()
            {
                node<T> * temp;
                node<T> * temp2;
                temp = head->next;
                temp2 = temp;
                temp = temp->next;
                temp->prev = head;
                head->next = temp;
                list_size--;
                delete temp2;
            }

            /// Recupera o último elemento da lista.
		    /*!
			*    @return A referência do valor do último elemento da lista.   */
            const T & back() const
            {
                return (tail->prev)->data;
            }

            /// Recupera o primeiro elemento da lista.
		    /*!
			*    @return A referência do valor do primeiro elemento da lista.   */
            const T & front() const
            {
                return (head->next)->data;
            }

            /// Retorna um iterator para o inicio da lista.
			/*! 
			*	@return Um iterator para o primeiro elemento da lista.  */
            iterator begin() const
            {
                return iterator(head->next);
            }

            /// Retorna um iterator para o final da lista.
			/*! 
			*	@return Um iterator para o elemento posterior ao último elemento da lista.  */
            iterator end() const
            {
                return iterator(tail);
            } 


            /// Insere um elemento em uma posicao especifica na lista.
			/*! 
			*	@param pos Um iterator que aponta para a posicao onde será inserido o elemento.
			*	@param value O valor a ser inserido.
			*	@return um iterator para a posicao onde foi inserido o valor      */
            iterator insert( iterator pos, const T & value )
            {
                iterator temp(pos.getprev());
                node <T> * temp2 = new node <T> ();
                temp2->data = value;
                temp2->next = temp.getnext();
                temp2->prev = pos.getprev();
                pos.getprev() = temp2;
                temp.getnext() = temp2;
                list_size++;
                return iterator(temp2);
            }

            /// Insere uma lista de elementos a partir de uma posicao especifica no vector.
			/*! 
			*	@param pos Um iterator que aponta para a posicao onde será inserido o elemento.
			*	@param ilist A lista inicializadora a ser inserida na lista encadeada.
			*	@return Um iterator para a posicao onde começou a inserção da lista inicializadora na lista encadeada.     */
            iterator insert( iterator pos, std::initializer_list<T> ilist) // Se lembrar de mudar o primeiro argumento para const_iterator
            {
                iterator aux = pos;
                aux--;
                for(auto e : ilist)
                {
                    insert(pos, e);
                }
                aux++;
                return aux;
            }

            /// Insere um range de elementos a partir de uma posicao especifica na lista.
			/*! 
			*	@param pos Um iterator que aponta para a posicao onde será inserido o range.
			*	@param first O inicio do range que será inserido na lista.
			*	@param last O final do range que será inserido na lista.
			*	@return um iterator para a posicao que foi o ponto de começo de inserção do range na lista.      */
            template < typename InItr>
            iterator insert( iterator pos, InItr first, InItr last )
            {

                iterator aux = pos;
                aux--;
				while(first != last)
                {
                    insert(pos, (*first));
                    first++;
                }
                aux++;
                return aux;

            }

            /// Remove um elemento em uma posicao especifica na lista.
			/*! 
			*	@param pos Um iterator que aponta para a posicao do elemento que será removido.
			*	@return um iterator para a posicao posterior a posicao do elemento removido.     */
            iterator erase( iterator pos ) 
            {
                iterator exit;
                exit = pos;
                exit++;
                node <T> * temp;
                node <T> * temp2;
                node <T> * temp3;
                temp = pos.getprev();
                temp2 = pos.getnext();
                temp3 = temp2->prev;
                temp->next = temp2;
                temp2->prev = temp;
                list_size--;
                delete temp3;
                return exit;
            }

            /// Remove um range de elementos especificados em uma lista.
			/*! 
			*	@param first Um iterator que aponta para a posicao inicial do range a ser removido.
			*	@param last Um iterator que aponta para a posicao final do range a ser removido.
			*	@return um iterator para a posicao posterior ao último elemento removido.    */
            iterator erase(iterator first, iterator last)
            {
            	
            	iterator exit;
            	while(first != last)
            	{
            		auto aux = first;
            		first++;
            		erase(aux);
            	}
            	
            	return last;
            }

             /// Insere múltiplas cópias de um elemento em uma lista.
		    /*!
		    *    @param count O número de cópias a ser copiado na lista .  
			*    @param value O elemento a ser copiado para a lista.      */
            void assign( size_type count, const T& value )
            {
                clear();
                for(size_type i = 0; i<count; i++)
                {
                    push_back(value);
                }
            }

            /// Substitui o conteúdo de uma lista encadeada pelo conteúdo de um range.
		    /*! 
			*    @param first O incio do range a ser copiada na lista encadeada. 
			*    @param last O final do range a ser copiada na lista encadeada.  */
            template < typename InItr>
			void assign( InItr first, InItr last )
			{
				clear();
				while(first != last)
                {
                    push_back((*first));
                    first++;
                }
               
			}

            /// Substitui o conteúdo de uma lista encadeada pelo conteúdo de uma lista inicializadora.
		    /*! 
			*    @param ilist A lista inicializadora a ser copiada na lista encadeada.   */
            void assign( std::initializer_list<T> ilist )
            {
                clear();
                for(auto e : ilist)
                {
                    push_back(e);
                }
            }

            /// Sobrecarga do operador de extração para uma lista encadeada.
            friend std::ostream &operator<<(std::ostream &os, const list<T> &A)
			{
			    node <T> * it;
			    it = A.head->next;
			    os << "[ ";
			    while(it != A.tail)
			    {
			        os << it->data << " ";
			    	it = it->next;
			    }
			    os << "]";

			    return os;
			};

    };

    /// Sobrecarga do operador de igualdade para duas listas encadeadas.
    template <typename T>
    bool operator==(const list <T> & lhs, const list <T> & rhs)
    {
            if(lhs.size() == rhs.size())
            {
                auto ltemp = lhs.begin();
                auto rtemp = rhs.begin();
                for(size_t i = 0; i<lhs.size(); i++)
                {
                    if((*ltemp) != (*rtemp)) return false;
                    ltemp++;
                    rtemp++;
                }

                return true;
            }

            else return false;

    }

    /// Sobrecarga do operador de desigualdade para duas listas encadeadas.
    template <typename T>
    bool operator!=(const list <T> & lhs, const list <T> & rhs)
    {
            if(lhs.size() == rhs.size())
            {
                auto ltemp = lhs.begin();
                auto rtemp = rhs.begin();
                for(size_t i = 0; i<lhs.size(); i++)
                {
                    if((*ltemp) != (*rtemp)) return true;
                    ltemp++;
                    rtemp++;
                }

                return false;
            }

            else return true;

    }




}


#endif