//
// Created by Noxianin on 2018-06-11.
//

#ifndef JIMP_EXERCISES_POSTORDERTREEITERATORS_H
#define JIMP_EXERCISES_POSTORDERTREEITERATORS_H
#include "../tree/Tree.h"
#include <vector>


namespace tree {


    template<typename T>
    class PostOrderTreeIterator {
    public:
        explicit PostOrderTreeIterator(std::shared_ptr<Tree<T>> root) {
            PlaceInOrder(root);
            index = 0;
        }

        void PlaceInOrder(std::shared_ptr<Tree<T>> tree) {
            if (tree->left_) PlaceInOrder(tree->left_);
            if (tree->right_) PlaceInOrder(tree->right_);
            order_.push_back(tree);
        }

        PostOrderTreeIterator<T> End() {
            index = order_.size();
            return *this;
        }

        PostOrderTreeIterator<T> operator++() {
            index++;
            return *this;
        }

        T operator*() {
            return order_[index]->Value();

        }

        bool operator!=(const PostOrderTreeIterator &other) const {
            return other.index != index;
        }

    private:
        std::vector<std::shared_ptr<Tree<T>>> order_;
        int index;
    };

    template<typename T>
    class PostOrderTreeView {
    public:
        explicit PostOrderTreeView(Tree<T> *tree) : root_{std::make_shared<Tree<T>>(*tree)} {};

        PostOrderTreeIterator<T> begin() {
            return PostOrderTreeIterator<T>(root_);
        }

        PostOrderTreeIterator<T> end() {
            return PostOrderTreeIterator<T>(root_).End();
        }

    private:
        std::shared_ptr<Tree<T>> root_;
    };

    template<typename T>
    PostOrderTreeView<T> PostOrder(Tree<T> *tree) {
        return PostOrderTreeView<T>(tree);
    }


}
#endif //JIMP_EXERCISES_POSTORDERTREEITERATORS_H
