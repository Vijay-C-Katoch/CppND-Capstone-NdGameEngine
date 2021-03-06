/*
* NdGameEngine
* 
* A very simple game engine which is derivation
* of olcPixelGameEngine developed by OneLoneCoder.com
* 
* Source Location: 
* https://github.com/Vijay-C-Katoch/CppND-Capstone-Asteroids
* 
* olcPixelGameEngine source location:
* https://github.com/OneLoneCoder/olcPixelGameEngine
* 
* License : 
* https://github.com/Vijay-C-Katoch/CppND-Capstone-Asteroids/blob/main/LICENSE.md  
* 
*/


#ifndef ND_GAME_ENGINE_H_
#define ND_GAME_ENGINE_H_

#include <cstdint>
#include <cmath>
#include <vector>
#include <atomic>
#include <memory>
#include <chrono>
#include <string>

#include "ndConfig.h"
#include "ndException.h"
#include "math/ndLinAlgebra.h"
#include "hw/keyboardController.h"
#include "mediaLibrary.h"

namespace nd
{
  namespace defaults 
  {
    constexpr std::uint8_t   alpha = 0xFF; //opacity. 255 = opaque
    constexpr std::uint32_t  pixelValue = (alpha <<24);
    constexpr float radian2Pi = 6.283185f;
    constexpr float radianPi = 3.141593f;
    constexpr float radianPiby2 = 1.570796f;
  }
   

  // Represents a 32 bit RGBA color
  struct Pixel
  {
    union
    {
      std::uint32_t data = defaults::pixelValue;
      struct { std::uint8_t r; std::uint8_t g; std::uint8_t b; std::uint8_t a; };
    };

    // Transparency mode
    enum class Tmode { NORMAL, ALPHA, MASK, CUSTOM };

    Pixel() = default;
    Pixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = defaults::alpha);
    Pixel(std::uint32_t p);
  };

  // useful Pixel constants
  static const Pixel
    WHITE(255, 255, 255),
    BLACK(0, 0, 0), BLANK(0, 0, 0, 0),
    RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
    GREEN(0, 255, 0), LIGHT_GREEN(0, 180, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
    BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
    GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
    YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
    CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
    MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64);
        

  // 2D Sprite game character representation
  class Sprite
  {
  public:
    Sprite() = default;
    Sprite(std::int32_t w, std::int32_t h);
    ~Sprite();

    Pixel GetPixel(std::int32_t x, std::int32_t y)const;
    void SetPixel(std::int32_t x, std::int32_t y, Pixel p);
    Pixel* GetDataPtr();

    std::int32_t Width()
    {
      return _width;
    }

    std::int32_t Height()
    {
      return _height;
    }


  private:
    std::int32_t _width = 0;
    std::int32_t _height = 0;
    std::vector<Pixel> _pixels;

  };

  class NdGameEngine
  {
  public:
    NdGameEngine() = default;
    ~NdGameEngine() = default;

    void ConstructGame(
      std::int32_t screen_w, std::int32_t screen_h, std::int32_t pixel_w = 1, 
      std::int32_t pixel_h = 1, bool full_screen = false
    );
    void Run();

  public: // Override interfaces for client
    virtual void onClientCreate();

    virtual void onClientUpdate(float elapsedTicks);

    virtual void onClientDestroy();  

  public: // Hardware Connect

    void ConnectKeyPressCb(const Key& key, const KeyControllerContext::KeyFunc_t& func)
    {
      _mediaLib.ConnectKeyPressCb(key, func);
    }
    void ConnectKeyReleaseCb(const Key& key, const KeyControllerContext::KeyFunc_t& func)
    {
      _mediaLib.ConnectKeyReleaseCb(key, func);
    }

    void OnQuitCb()const;

  public: // Utility
      std::int32_t GetDrawTargetWidth();

      std::int32_t GetDrawTargetHeight();

      std::uint32_t ScreenWidth() const
      {
        return _screenWidth;
      }

      std::uint32_t ScreenHeight() const
      {
        return _screenHeight;
      }

      float WrapX(float x, std::uint32_t grid_width = 0)
      {
        if (!grid_width) { grid_width = _screenWidth; }

        return std::abs((std::fmod((x + grid_width), grid_width)));
      }

      float WrapY(float y, std::uint32_t grid_height = 0)
      {
        if (!grid_height) { grid_height = _screenHeight; }

        return std::abs((std::fmod((y + grid_height), grid_height)));
      }

      float ElapsedTicks() const
      {
        return _elapsedTicks;
      }

      bool isInsideCircle(float cx, float cy, float radius, float x, float y) const;

  public: // Draw methods
      void SetDrawTarget(std::unique_ptr<Sprite> target);
      virtual void Draw(std::int32_t x, std::int32_t y, Pixel p = WHITE);
      void DrawLine(std::int32_t x1, std::int32_t y1, std::int32_t x2, std::int32_t y2, Pixel p = WHITE);
      void DrawRectangle(std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, Pixel p = WHITE);
      void DrawWireFrame(const std::vector<ndVector<float>>& model, const ndVector<float>& trlVec, float r = 0.0f, float s = 1.0f, Pixel p = WHITE);
      void DrawString(std::int32_t x, std::int32_t y, const std::string& text, Pixel p = WHITE, std::uint32_t scale = 1);
    
      // Clears Screen by changing draw target to given Pixel
      void ClearScreen(Pixel p);

  public:
    // initialization
    void FontInit();

  public:
      // Engine thread management
      void EngineInit();
      void EngineCoreUpdate();   


  private:
      std::unique_ptr<Sprite> _drawTarget;
      std::unique_ptr<Sprite> _fontTarget;
      Pixel::Tmode _pixelMode = Pixel::Tmode::NORMAL;
      float _pixelBlendFactor = 1.0f;
      std::uint32_t	_screenWidth = 256;
      std::uint32_t	_screenHeight = 240;
      std::int32_t _windowWidth = 0;
      std::int32_t _windowHeight = 0;
      std::uint32_t	_pixelWidth = 4;
      std::uint32_t	_pixelHeight = 4;
      bool _fullScreen;

      // time
      std::chrono::time_point<std::chrono::system_clock> _tp1, _tp2;
      float _elapsedTicks;

      MediaLib _mediaLib;

      void GameEngineThread();
  };

  // Game Engine Exceptions type
  using PixelException = ClassException<Pixel, RuntimeException>;
  using SpriteException = ClassException<Sprite, RuntimeException>;
  using GameEngineException = ClassException<NdGameEngine, RuntimeException>;

  // Concurrency
  extern std::atomic<bool> g_isEngineRunning;


} // namespace nd

#endif /* ND_GAME_ENGINE_H_ */
