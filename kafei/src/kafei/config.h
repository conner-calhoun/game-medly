#ifndef CONFIG_H
#define CONFIG_H

namespace kafei {

class Config {
   public:
    Config() {}
    void set_window_title(std::string title) {
        main_title = title;
    }
    std::string get_title() {
        return main_title;
    }

   private:
    std::string main_title;
};

}  // namespace kafei

#endif  // CONFIG_H