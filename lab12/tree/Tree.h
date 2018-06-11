

#ifndef JIMP_EXERCISES_TREE_H
#define JIMP_EXERCISES_TREE_H
#include <memory>
namespace tree
{
    template <typename T>
    class Tree
    {
    public:
        Tree() : left_{nullptr}, right_{nullptr}{};
        explicit Tree(const T & value): right_{nullptr}, left_{nullptr}, value_{std::make_shared<T>(value)}{};

        T Value() const
        {
            return *value_;
        }

        std::shared_ptr<Tree<T>> Left() const
        {
            return left_;
        }

        std::shared_ptr<Tree<T>> Right() const
        {
            return right_;
        }



        void Insert(const T & element)
        {
            if(element<*value_)
            {
                if (left_== nullptr)
                {
                    left_ = std::make_shared<Tree<T>>(Tree(element));
                }
                else
                {
                    left_->Insert(element);
                }

            }
            else
            {
                if(right_== nullptr)
                {
                    right_ = std::make_shared<Tree<T>>(Tree(element));
                }
                else
                {
                    right_ ->Insert(element);
                }

            }

        }

        bool Find(const T &element)
        {
            if (value_ == element) return true;

            if(value_>element)
            {
                if(left_== nullptr) return false;
                else
                {
                    left_ ->Find(element);
                }
            }
            else
            {
                if(right_== nullptr) return false;
                else
                {
                    right_ ->Find(element);
                }
            }
        }

        size_t Size()
        {
            if(!left_ && !right_) return 1;
            if(!left_) return 1 + right_->Size();
            if(!right_) return 1+left_ ->Size();
            return right_->Size()+left_->Size()+1;
        }

        size_t Depth()
        {
            if(!left_&&!right_) return 1;
            if(!left_) return 1 + right_->Depth();
            if(!right_) return 1+ left_->Depth();
            return std::max(right_->Depth(),left_->Depth())+1;
        }

        std::shared_ptr<Tree<T>> Root()
        {
            return std::make_shared<Tree<T>>(*this);
        }


        std::shared_ptr<T> value_;
        std::shared_ptr<Tree<T>> left_;
        std::shared_ptr<Tree<T>> right_;

    };
}
#endif //JIMP_EXERCISES_TREE_H
