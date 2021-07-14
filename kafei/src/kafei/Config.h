#ifndef CONFIG_H
#define CONFIG_H

namespace kafei {

class Config {
   public:
    Config() {}
    void SetWindowTitle(std::string title) {
        _mainTitle = title;
    }
    std::string GetTitle() {
        return _mainTitle;
    }

   private:
    std::string _mainTitle;
};

}  // namespace kafei

#endif  // CONFIG_H