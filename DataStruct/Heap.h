#ifndef HEAP_H
#define HEAP_H

#include <vector>
struct HeapNode
{
    int index_;
    HeapNode();
    void set_heap_index(const int index);
    int heap_index() const;
};
inline HeapNode::HeapNode() : index_(-1) {}

inline void HeapNode::set_heap_index(const int index)
{
    this->index_ = index;
}

inline int HeapNode::heap_index() const
{
    return this->index_;
}

//calc index
#define INDEX_PARENT(X) \
    (((X) - 1) >> 1)
#define INDEX_LEFT_CHILD(X) \
    (((X) << 1 ) + 1)
#define INDEX_RIGHT_CHILD(X) \
    (((X) << 1) + 2)

template<typename Obj, typename Compare = std::less<Obj>>
class Heap
{
    typedef std::vector<Obj*> ObjList;
public:
    Heap();
    ~Heap();
    void clear();

    int size();
    Obj* top();
    Obj* pop();
    void push(Obj *obj);
    int remove(Obj *obj);
    Obj* remove(const int index);
    Obj* node(const int index);

    int adjust_from_top(int index);
    int adjust_from_bottom(int index);

private:
    Compare compare_func_;
    ObjList obj_list_;
    int current_size_;
};

template<typename Obj, typename Compare>
Heap<Obj, Compare>::Heap() : current_size_(0) {}

template<typename Obj, typename Compare>
Heap<Obj, Compare>::~Heap()
{
    this->clear();
}

template<typename Obj, typename Compare>
void Heap<Obj, Compare>::clear()
{
    for (int i = 0; i < this->current_size_; ++i)
    {
        if (this->obj_list_[i])
        {
            Obj *obj = this->obj_list_[i];
            obj->set_heap_index(-1);
        }
    }
    this->obj_list_.clear();
    this->current_size_ = 0;
}

template<typename Obj, typename Compare>
int Heap<Obj, Compare>::size()
{
    return this->current_size_;
}

template<typename Obj, typename Compare>
Obj* Heap<Obj, Compare>::top()
{
    if (this->current_size_ <= 0)
        return 0;

    return this->obj_list_[0];
}

template<typename Obj, typename Compare>
Obj* Heap<Obj, Compare>::pop()
{
    if (this->current_size_ <= 0)
        return 0;

    Obj* obj = this->obj_list_[0];
    this->obj_list_[0] = this->obj_list_[--this->current_size_];
    this->obj_list_[0]->set_heap_index(0);
    this->obj_list_[this->current_size_] = 0;

    this->adjust_from_top(0);

    obj->set_heap_index(-1);
    return obj;
}

template<typename Obj, typename Compare>
void Heap<Obj, Compare>::push(Obj* obj)
{
    int index = this->current_size_;
    obj->set_heap_index(index);

    if (index >= (int)this->obj_list_.size())
    {
        this->obj_list_.push_back(obj);
    }
    else
    {
        this->obj_list_[index] = obj;
    }

    ++this->current_size_;
    this->adjust_from_bottom(index);
}

template<typename Obj, typename Compare>
int Heap<Obj, Compare>::remove(Obj *obj)
{
    int index = obj->heap_index();
    if (index < 0 || index > this->current_size_)
        return -1;
    
    Obj *remove_obj = this->obj_list_[index];
    if (remove_obj != obj)
        return -1;

    if (this->remove(index) == 0)
        return -1;
    return 0;
}

template<typename Obj, typename Compare>
Obj* Heap<Obj, Compare>::remove(const int index)
{
    int cur_index = index;
    if (cur_index < 0 || cur_index > this->current_size_)
        return 0;

    Obj *cur_node = this->node(cur_index);
    if (cur_index == this->current_size_-1)
    {
        this->obj_list_[cur_index] = 0;
        --this->current_size_;
    }
    else
    {
        Obj *adjust_node = this->obj_list_[--current_size_];
        this->obj_list_[current_size_] = 0;
        this->obj_list_[cur_index] = adjust_node;
        adjust_node->set_heap_index(cur_index);

        int parent_index = INDEX_PARENT(cur_index);
        Obj *parent_node = this->node(parent_index);
        if (parent_node != NULL 
            && this->compare_func_(*adjust_node, *parent_node) == true 
            && this->compare_func_(*parent_node, *adjust_node) == false)
        {
            this->adjust_from_bottom(cur_index);
        }
        else
        {
            this->adjust_from_top(cur_index);
        }
    }

    if (cur_node != 0)
        cur_node->set_heap_index(-1);

    return cur_node;
}

template<typename Obj, typename Compare>
Obj* Heap<Obj, Compare>::node(const int index)
{
    if (index < 0 || index > this->current_size_)
        return 0;
    
    return this->obj_list_[index];
}

template<typename Obj, typename Compare>
int Heap<Obj, Compare>::adjust_from_top(int index)
{
    if (index < 0 || index >= this->current_size_)
        return -1;

    int cur_index, left_index, right_index, compare_index;
    cur_index = index;
    left_index = INDEX_LEFT_CHILD(cur_index);
    right_index = INDEX_RIGHT_CHILD(cur_index);

    Obj *cur_node, *left_node, *right_node, *compare_node;
    cur_node = this->node(cur_index);
    left_node = this->node(left_index);
    right_node = this->node(right_index);

    while(left_node != 0 || right_node != 0)
    {
        compare_node = 0;
        compare_index = -1;
        if (left_node == 0)
        {
            compare_node = right_node;
            compare_index = right_node->heap_index();
        }
        else if (right_node == 0)
        {
            compare_node = left_node;
            compare_index = left_node->heap_index();
        }
        else
        {
            if (this->compare_func_(*left_node, *right_node) == true)
            {
                compare_node = left_node;
                compare_index = left_node->heap_index();
            }
            else
            {
                compare_node = right_node;
                compare_index = right_node->heap_index();
            }
        }

        if (this->compare_func_(*cur_node, *compare_node) == true)
            break;
        
        if (this->compare_func_(*compare_node, *cur_node) == false)
            break;

        compare_node->set_heap_index(cur_index);
        this->obj_list_[cur_index] = compare_node;

        cur_node->set_heap_index(compare_index);
        this->obj_list_[compare_index] = cur_node;

        cur_index = compare_index;
        left_index = INDEX_LEFT_CHILD(cur_index);
        right_index = INDEX_RIGHT_CHILD(cur_index);
        left_node = this->node(left_index);
        right_node = this->node(right_index);
    }

    return 0;
}

template<typename Obj, typename Compare>
int Heap<Obj, Compare>::adjust_from_bottom(int index)
{
    if (index <= 0 || index >= this->current_size_)
        return -1;
    
    int cur_index = index;
    int parent_index = INDEX_PARENT(index);
    Obj* parent_node = this->node(parent_index);
    Obj* cur_node = this->node(cur_index);
    while (parent_node != 0)
    {
        if (this->compare_func_(*cur_node, *parent_node) == false)
            break;

        parent_node->set_heap_index(cur_index);
        this->obj_list_[cur_index] = parent_node;

        cur_node->set_heap_index(parent_index);
        this->obj_list_[parent_index] = cur_node;

        cur_index = parent_index;
        parent_index = INDEX_PARENT(cur_index);
        parent_node = this->node(parent_index);
    }

    return 0;
}

#endif