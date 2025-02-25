#ifndef BLOCK_H
#define BLOCK_H

#define ROWS 21
#define COLUMNS 80

class Block {
public:
    char icon;
    int color;
    int x, y;

    virtual void Tick(Block* map[ROWS][COLUMNS]) = 0; //TEMP COLUMNS CHANGE LATER!!!!!!

    virtual ~Block() {} 

protected:
    Block(int x, int y) : x(x), y(y) {}
};

class Grass : public Block {
public:
    Grass(int x, int y) noexcept;
    void Tick(Block* map[ROWS][COLUMNS]) override;
};

class Mycelium : public Block {
    public:
        Mycelium(int x, int y) noexcept;
        void Tick(Block* map[ROWS][COLUMNS]) override;
    };   

class Dirt : public Block {
public:
    Dirt(int x, int y) noexcept;
    void Tick(Block* map[ROWS][COLUMNS]) override;
};

#endif