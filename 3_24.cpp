#include <iostream>

int get_number();

class c_tree
{
private:
    struct t_node
    {   
        int level;
        int data;
        int count_sons;
        t_node **sons;
    };

    // Pointer to the root of the tree
    t_node *root;

    // Create a 'node'
    t_node *create_node()
    {
        t_node *node = new t_node;  
        
        node->level = 0;
        node->data = 0;
        node->count_sons = 0;  	
        node->sons = nullptr;  	
        
        return node;
    }

    // Create 'sons' for the tree
    void create_son( t_node *_node, t_node *_son )
    {
        t_node **sons = new t_node *[ _node->count_sons + 1 ];
        for( int i = 0; i < _node->count_sons; i++ )
            sons[ i ] = _node->sons[ i ];

        sons[ _node->count_sons ] = _son;  	
        _node->sons = sons;  	
        _node->count_sons++;
    }

    void enter_data( t_node *_node, int  _level = 0 )
    {
        int _data = 0, _count_son = 0;

        std::cout << "[data] Please, enter some number: ";
        _data = get_number();
        _node->data = _data; // Filling the value into the tree

        _node->level = _level;

        std::cout << "[count]: Please, enter some number of subtrees: ";
        _count_son = get_number(); // Number of subtrees
        if( _count_son != 0 ) _level++;

        for( int i = 0; i < _count_son; i++ )
        {
            t_node *son = create_node();  	 	
            enter_data( son, _level );  	 	
            create_son( _node, son );
        }
    }

    // Displaying the entire tree completely
    void print_tree( t_node *_node, int a = 0)
    {
        // Indenting subtrees
        for( int i = 0; i < a; i++ )
            std::cout << " ";

        std::cout << _node->data << " [ " << _node->level << " ]" << std::endl;  	
        for( int i = 0; i < _node->count_sons; i++ )
            print_tree( _node->sons[ i ], a + 3 );
    }

    // Delete the tree starting with the last son
    void remove_node( t_node *_node )
    { 
        for( int i = 0; i < _node->count_sons; i++ ) 
        { 
            // We reach the last son
            if( _node->sons[ i ] != nullptr )  
                remove_node( _node->sons[i] ); 
        } 

        // Deleting..
        delete[] _node->sons; 
        delete _node; 
    }

    // Finding all subtrees on assignment
    void get_task( t_node *_node, t_node *_prev_node )
    {
        // Do we have a parent and leaves?
        if( _node->count_sons != 0 && _prev_node != nullptr )
        {
            if( _node->level % 2 )
                std::cout << "[odd]: " << _node->data << std::endl; 
            else
                std::cout << "[even]: " << _node->data << std::endl;
        }

        // Recursive call for subtrees
        for( int i = 0; i < _node->count_sons; i++ )
            get_task( _node->sons[ i ], _node );
    }

public:
    // Constructor / Destructor
    c_tree() { root = create_node(); }
    ~c_tree() { remove_node( root ); }

    // Enter the number of subtrees / their values
    void enter_data() { enter_data( root ); } 

    // Displaying a tree
    void print_tree() { print_tree( root ); }

    // Job function
    void get_task() { get_task( root, nullptr ); }
    
};

int main( void )
{   
    // Creating a tree
    c_tree tree;

    // Enter and print tree values
	tree.enter_data();
	tree.print_tree( );

    tree.get_task();

	system("pause"); 

    return EXIT_SUCCESS;
}

/**
 * Getting a number with a check for letters, etc.
*/
int get_number()
{
    int ret = 0;

    // Get 'ret' & Check that only numbers are entered
    while( !( std::cin >> ret ) || std::cin.peek() != '\n' )
    {
        std::cin.clear();
        while( std::cin.get() != '\n');
        std::cout << "Allowed only numbers!" << std::endl;;
    }

    // Returning the final value
    return ret;
}