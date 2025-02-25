#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
    char icon;
    int color;

    virtual ~Block() {} 
};

class Grass : public Block {
public:
    Grass() noexcept;
};

class Dirt : public Block {
public:
    Dirt() noexcept;
};

#endif