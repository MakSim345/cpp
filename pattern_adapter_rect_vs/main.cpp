#include "gen.h"

typedef int Coordinate;
typedef int Dimension;

// Desired interface
class Rectangle
{
  public:
    virtual void draw() = 0;
};

// Legacy component
class RectangleLegacy
{
  public:
    RectangleLegacy(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
    {
        x1_ = x1;
        y1_ = y1;
        x2_ = x2;
        y2_ = y2;
        cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
          << x2_ << "," << y2_ << ")" << endl;
    }
    void DisplayMe()
    {
        cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ << 
          ") => (" << x2_ << "," << y2_ << ")" << endl;
    }
  private:
    Coordinate x1_;
    Coordinate y1_;
    Coordinate x2_;
    Coordinate y2_;
};

// Adapter wrapper
class RectangleAdapter: public Rectangle, private RectangleLegacy
{
public:
    RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h):
      RectangleLegacy(x, y, x + w, y + h)
    {
        cout << "RectangleAdapter: create.  (" << x << "," << y << 
          "), width = " << w << ", height = " << h << endl;
    }

    virtual void draw()
    {
        cout << "RectangleAdapter: draw." << endl;
        DisplayMe();
    }
};


// Legacy component
class RectangleNew: public Rectangle
{
public:
    RectangleNew(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
    {
        x1_ = x1;
        y1_ = y1;
        x2_ = x2;
        y2_ = y2;
        cout << "RectangleNew:  create.  (" << x1_ << "," << y1_ << ") => ("
            << x2_ << "," << y2_ << ")" << endl;
    }
    void draw()
    {
        cout << "RectangleNew:  Draw.  (" << x1_ << "," << y1_ << 
            ") => (" << x2_ << "," << y2_ << ")" << endl;
    }
private:
    Coordinate x1_;
    Coordinate y1_;
    Coordinate x2_;
    Coordinate y2_;
};

class MainApp
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        
        Rectangle *r = new RectangleNew(120, 200, 60, 40);
        this->DrawTheObject(r);
        // r->draw();

        // now draw old Rectangle
        r = new RectangleAdapter(120, 200, 60, 40);
        this->DrawTheObject(r);
        // r->draw();
        return 0;
    }

    void DrawTheObject(Rectangle* _rect) const
    {
        // method take Rectangle as parameter and call draw() method from it.
        // obviously, RectangleLegacy do not have such method, 
        // so it was wrapped to RectangleAdapter:
        _rect->draw();
    }

    ~MainApp()
    {
        std::cout << "App: Good bye!\n";
    }

};


int main()
{
    
    std::auto_ptr <MainApp> _my_rect(new MainApp());
    
    _my_rect->Run();
    
    system ("PAUSE");
    return 1;
}
