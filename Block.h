#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
    virtual ~Block() {} 
    virtual char getIcon() const = 0; 
    virtual int getColor() const = 0;
};

class Grass : public Block {
public:
    Grass() noexcept;
    char getIcon() const override;
    int getColor() const override;
};

class Dirt : public Block {
public:
    Dirt() noexcept;
    char getIcon() const override;
    int getColor() const override;
};

#endif