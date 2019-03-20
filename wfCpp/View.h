#ifndef VIEW_H
#define VIEW_H

class View {
public:
    void virtual        draw()          = 0;
    void virtual        run()           = 0;
    void virtual        clearScreen()   = 0;

    virtual             ~View()         = 0;

    static              View * inst;
    static              View * get();
    virtual void        getWinSize()    = 0;
};

#endif
