#ifndef BLOCK_H
#define BLOCK_H

#define ROWS 21
#define COLUMNS 80

class Block {
public:
    char icon;
    int color;
    int x, y;

    virtual void Tick(Block*** map, int rows, int columns) = 0; 

    virtual ~Block() {} 

protected:
    Block(int x, int y) : x(x), y(y) {}
};

class Grass : public Block {
public:
    Grass(int x, int y) noexcept;
    void Tick(Block*** map, int rows, int columns) override;
};

class Mycelium : public Block {
    public:
        Mycelium(int x, int y) noexcept;
        void Tick(Block*** map, int rows, int columns) override;
    };   

class Dirt : public Block {
public:
    Dirt(int x, int y) noexcept;
    void Tick(Block*** map, int rows, int columns) override;
};

class Wheat : public Block {
    public:
        int stage;
        Wheat(int x, int y) noexcept;
        void Tick(Block*** map, int rows, int columns) override;
    };

#endif