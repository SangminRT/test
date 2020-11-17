/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:45:44 by sanhan            #+#    #+#             */
/*   Updated: 2020/11/17 23:19:32 by sanhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/mlx/mlx.h"
# include "./get_next_line_bonus.h"
# include "../libs/Libft/libft.h"
# include <unistd.h>
# include <float.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define KEY_ESC 53

# define KEY_LEFT 123
# define KEY_RIGHT 124

# define SCREENWIDTH 640
# define SCREENHEIGHT 480

# define X_EVENT_KEY_PRESS   2
# define X_EVENT_KEY_EXIT    17
# define TEXTURE_KIND 5

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		distance;
}				t_sprite;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_cub
{
	int			render_size_x;
	int			render_size_y;
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		*sprite_path;
	int			player_check;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_row;
	int			map_col;
	int			sprite_count;
}				t_cub;

typedef struct	s_wall_casting
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			step;
	int			tex_pos;
}				t_wall_casting;

typedef struct	s_sprite_casting
{
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
}				t_sprite_casting;

typedef struct	s_img
{
	void		*img;
	int			*data;

	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_info
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx;
	void		*win;
	double		move_speed;
	double		rot_speed;
	t_img		img;
	t_cub		*cub;
	t_pos		*texture_size;
	t_sprite	*sprite;
	char		**max_pad;
	int			**buf;
	double		*z_buffer;
	int			**texture;
	int			*sprite_order;
	double		*sprite_dist;
	int			sprite_count;
}				t_info;

/*
** main.c
*/
void			calc(t_info *info);
void			draw(t_info *info);

/*
** init.c
*/
void			init_info(t_info *info, char *path);
void			init_info_rest(t_info *info);
void			init_cub(t_cub *cub);
void			load_texture(t_info *info);
void			load_image(t_info *info, int i, char *path, t_img *img);

/*
** bmp.c
*/
void			bmp_main(t_info *info, char *path);
int				save_bmp(t_info *info);
void			write_data(t_info *info, int fd);
void			write_bmp_header(t_info *info, int fd, int size);
void			set_int_in_char(unsigned char *start, int value);

/*
** cub_parse.c
*/
void			cub_read_file(t_info *info, const char *path);
void			cal_max_column(t_cub *cub);
char			*cub_read_line(const char *path);
void			cub_parse_element(t_cub *cub, char **cub_temp);

/*
** cub_parse_nswe.c
*/
void			cub_parse_nswe(t_cub *cub, char **temp);
void			setup_no_path(t_cub *cub, char *path);
void			setup_so_path(t_cub *cub, char *path);
void			setup_we_path(t_cub *cub, char *path);
void			setup_ea_path(t_cub *cub, char *path);

/*
** cub_parse_rsfc.c
*/
void			cub_parse_rest(t_cub *cub, char **temp, int split_count);
void			cub_parse_res(t_cub *cub, char **temp, int split_count, int c);
void			cub_parse_c(t_cub *cub, char **color);
void			cub_parse_f(t_cub *cub, char **color);

/*
** cub_parse_map.c
*/
void			cub_parse_map(t_cub *cub, char **line, int line_count);
int				map_count_end_space(char *s);
void			cub_map_checkout(t_info *info);
void			cub_save_sprite(t_info *info);
void			map_pre_validity(t_info *info, int i, int j);

/*
** cub_init_player.c
*/
void			cub_set_player(t_info *info, char pos, int i, int j);
void			cub_set_player_n(t_info *info);
void			cub_set_player_s(t_info *info);
void			cub_set_player_w(t_info *info);
void			cub_set_player_e(t_info *info);

/*
** key_wsad.c
*/
void			move_player_w(t_info *info);
void			move_player_s(t_info *info);
void			move_player_a(t_info *info);
void			move_player_d(t_info *info);

/*
** key_arrow.c
*/
void			move_player_arrow(t_info *info, int key_num);
void			update_right(t_info *info, double old_dir_x,
							double old_plane_x);
void			update_left(t_info *info, double old_dir_x, double old_p_x);

/*
** map_check.c
*/
void			check_map_valid(t_info *info, double pos_x, double pos_y);
char			**create_padded_square(t_info *info);
int				is_valid_map(t_info *info, int x, int y, int *visited);
void			fill_rest(t_info *info, char **max_pad);
void			set_top_bot_space(t_info *info, char **max_pad);

/*
** error.c
*/
void			error_exit(char *msg);
void			check_valid_file(char *filepath);

/*
** util.c
*/
void			floor_ceiling_to_buffer(t_info *info, int x);
void			free_two_dimension_array(char **ptr);
int				screen_exit(void);
void			init_vector(t_pos *to, int x, int y);

/*
** raycasting_wall.c
*/
void			wall_to_buffer(t_info *info, int x);
void			init_ray(int x, t_info *info, t_wall_casting *ray);
void			calculate_wall_texture(t_info *info, t_wall_casting *ray);
void			find_and_calc_wall(t_info *info, t_wall_casting *ray);
void			set_step_and_side(t_info *info, t_wall_casting *ray);

/*
** raycasting_sprite.c
*/
void			draw_sprite(t_info *info, int i);
void			draw_spr_tex(t_info *info, t_sprite_casting *rs, int count);
void			init_ray_sprite(t_info *info, t_sprite_casting *rs, int i);
void			sort_sprites(t_info *info);

#endif
