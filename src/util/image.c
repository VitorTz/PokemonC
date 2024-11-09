#include "image.h"


void image_init(image_t* img, const char* file_name) {
	img->texture = texture_pool_get(file_name);
	img->size.x = (float) img->texture->width;
	img->size.y = (float) img->texture->height;	
	img->pos = (Vector2){ 0.0f, 0.0f };	
}


void image_draw(image_t* img) {
	DrawTextureV(*img->texture, img->pos, WHITE);
}


void image_draw_rect(image_t* img, const Rectangle* rect) {
	DrawTextureRec(*img->texture, *rect, img->pos, WHITE);
}


void image_set_center(image_t* img, const float x, const float y) {
	img->pos.x = x - img->size.x / 2.0f;
	img->pos.y = y - img->size.y / 2.0f;
}