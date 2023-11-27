#include<stdio.h>

typedef enum
{
    Edit,
    View,
    Help
}Operation;

typedef enum
{
    success,
    failure
}Status;

typedef enum
{
    m_title,
    m_album,
    m_artist,
    m_year,
    m_genre,
    m_comment
}tags;


typedef enum
{
    t,
    a,
    A,
    y,
    m,
    c
}edittags;