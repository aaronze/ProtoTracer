#include "QuadTree.h"

QuadTree::QuadTree(const BoundingBox2D& bounds) : bbox(bounds) {}

QuadTree::~QuadTree() {
    free(entities);
}

bool QuadTree::Insert(Triangle2D* triangle) {
    bool inserted = root.Insert(triangle, bbox);
    if (inserted)
        ++count;
    return inserted;
}

void QuadTree::Expand(int newCapacity) {
    entities = (Triangle2D*)realloc(entities, newCapacity * sizeof(Triangle2D));
    capacity = newCapacity;
}

bool QuadTree::Insert(Triangle2D triangle) {
    if (count == capacity)
        Expand(capacity ? (1.5f * capacity) : maxEntities);

    entities[count] = triangle;

    bool inserted = root.Insert(&entities[count], bbox);

    if (inserted)
        ++count;

    return inserted;
}

Node* QuadTree::Intersect(const Vector2D& p) {
    Node* currentNode = &root;
    BoundingBox2D currentBbox = bbox;
    while (true) {
        if (currentNode->IsLeaf())
            return currentNode;

        Vector2D mid = { (currentBbox.GetMinimum().X + currentBbox.GetMaximum().X) * 0.5f, (currentBbox.GetMinimum().Y + currentBbox.GetMaximum().Y) * 0.5f };

        BoundingBox2D bboxes[] = { {currentBbox.GetMinimum(), mid}, {{mid.X, currentBbox.GetMinimum().Y}, {currentBbox.GetMaximum().X, mid.Y}},
            {{currentBbox.GetMinimum().X, mid.Y}, {mid.X, currentBbox.GetMaximum().Y}}, {mid, currentBbox.GetMaximum()} };

        bool found = false;

        for (int i = 0; i < 4; ++i) {
            if (bboxes[i].Contains(p)) {
                currentNode = &(currentNode->GetChildNodes()[i]);
                currentBbox = bboxes[i];
                found = true;
                break;
            }
        }

        if (!found)
            return nullptr;
    }
}

void QuadTree::Rebuild() {
    for (int i = 0; i < count; ++i)
        root.GetEntities()[i] = &entities[i];

    root.Subdivide(bbox);
}

void QuadTree::PrintStats() {
    int totalCount = 0;
    //printf("total inserts: %d\n", count);
    //printf("node stats: \n");
    root.PrintStats(totalCount, bbox);
    //printf("total entities: %d \n", totalCount);
}
