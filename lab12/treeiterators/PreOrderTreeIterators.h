//
// Created by Noxianin on 2018-06-11.
//

#ifndef JIMP_EXERCISES_PREORDERTREEITERATORS_H
#define JIMP_EXERCISES_PREORDERTREEITERATORS_H
#include "../tree/Tree.h"
#include <vector>
#include <memory>



namespace tree {
    template<typename T>
    class PreOrderTreeIterator {
    public:
        explicit PreOrderTreeIterator(std::shared_ptr<Tree<T>> root) {
            PlaceInOrder(root);
            index = 0;
        }

        void PlaceInOrder(std::shared_ptr<Tree<T>> tree) {
            order_.push_back(tree);
            if (tree->left_) PlaceInOrder(tree->left_);
            if (tree->right_) PlaceInOrder(tree->right_);
        }

        PreOrderTreeIterator<T> End() {
            index = order_.size();
            return *this;
        }

        PreOrderTreeIterator<T> operator++() {
            index++;
            return *this;
        }

        T operator*() {
            return order_[index]->Value();

        }

        bool operator!=(const PreOrderTreeIterator &other) const {
            return other.index != index;
        }

    private:
        std::vector<std::shared_ptr<Tree<T>>> order_;
        int index;
    };

    template<typename T>
    class PreOrderTreeView {
    public:
        explicit PreOrderTreeView(Tree<T> *tree) : root_{std::make_shared<Tree<T>>(*tree)} {};

        PreOrderTreeIterator<T> begin() {
            return PreOrderTreeIterator<T>(root_);
        }

        PreOrderTreeIterator<T> end() {
            return PreOrderTreeIterator<T>(root_).End();
        }

    private:
        std::shared_ptr<Tree<T>> root_;
    };

    template<typename T>
    PreOrderTreeView<T> PreOrder(Tree<T> *tree) {
        return PreOrderTreeView<T>(tree);
    }

}
#endif //JIMP_EXERCISES_PREORDERTREEITERATORS_H
