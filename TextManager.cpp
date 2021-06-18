#include "TextManager.h"

void TextManager :: init() {
    if (TTF_Init() == 0){
        std :: cout << "TTF initialized..." << std :: endl;
    }
}

TextInfo TextManager :: renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer, int w, int h) {
        //Открываем шрифт
        TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
//        if (font == nullptr){
//            return nullptr;
//        }
        //Сначала нужно отобразить на поверхность с помощью TTF_RenderText,
        //затем загрузить поверхность в текстуру
        SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
//        if (surf == nullptr){
//            TTF_CloseFont(font);
//            return nullptr;
//        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (texture == nullptr){
        }
        //Очистка поверхности и шрифта
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        int x, y, iW, iH;
        TextInfo info;
        SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
        iW = w;
        iH = h;
        x = width / 2 - iW / 2;
        y = height / 2 - iH / 2;
        info.text = message;
        info.xPosition = x;
        info.yPosition = y;
        info.width = iW;
        info.height = iH;
        info.texture = texture;
        info.color.r = color.r;
        info.color.g = color.g;
        info.color.b = color.b;
        info.color.a = color.a;
        return info;
}
TextInfo TextManager :: renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer *renderer) {
        //Открываем шрифт
        TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
//        if (font == nullptr){
//            return nullptr;
//        }
        //Сначала нужно отобразить на поверхность с помощью TTF_RenderText,
        //затем загрузить поверхность в текстуру
        SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
//        if (surf == nullptr){
//            TTF_CloseFont(font);
//            return nullptr;
//        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (texture == nullptr){
        }
        //Очистка поверхности и шрифта
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        int x, y, iW, iH;
        TextInfo info;
        SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
        x = width / 2 - iW / 2;
        y = height / 2 - iH / 2;
        info.text = message;
        info.xPosition = x;
        info.yPosition = y;
        info.width = iW;
        info.height = iH;
        info.texture = texture;
        info.color.r = color.r;
        info.color.g = color.g;
        info.color.b = color.b;
        info.color.a = color.a;
        return info;
}
