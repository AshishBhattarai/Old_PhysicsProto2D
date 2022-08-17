#ifndef CONFIG_2D_H
#define CONFIG_2D_H

#ifdef OBJECT_VERTEX_SHADER
#define VERT_A_POSITION_LOC 0
#define VERT_UB_GENERAL_LOC 0
#define VERT_U_TRANSFORMATION_LOC 0
#endif

#ifdef OBJECT_FRAGMENT_SHADER
#define FRAGMENT_SHADER
#define FRAG_U_OBJ_TYPE_LOC 5
#define FRAG_U_OBJ_COLOR_LOC 6
#endif

#if defined(OBJECT_VERTEX_SHADER) || defined(OBJECT_FRAGMENT_SHADER)
#define VERT_INTERFACE_BLOCK_LOC 0
#endif

/**
 *
 *
 *
 *
 */

#ifdef LINE_VERTEX_SHADER
#define VERT_A_POSITION_LOC 0
#define VERT_UB_GENERAL_LOC 0
#endif

#ifdef LINE_FRAGMENT_SHADER
#define FRAGMENT_SHADER
#define FRAG_U_LINE_COLOR_LOC 5
#define FRAG_U_LINE_THICK_LOC 6
#define FRAG_U_LINE_P1 7
#define FRAG_U_LINE_P2 8
#endif

#if defined(LINE_VERTEX_SHADER) || defined(LINE_FRAGMENT_SHADER)
#define VERT_INTERFACE_BLOCK_LOC 0
#endif

/**
 *
 *
 *
 *
 */

#ifdef VERTEX_SHADER
// attribute locations
#define VERT_A_POSITION_LOC 0
#define VERT_A_NORMAL_LOC 1
// uniform block
#define VERT_UB_GENERAL_LOC 0
#endif

#ifdef FRAGMENT_SHADER
#define COLOR_ATTACHMENT0 0
#endif

#endif
