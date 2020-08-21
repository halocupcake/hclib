#ifndef HC_DESTRUCTOR_H
#define HC_DESTRUCTOR_H

#ifdef __cplusplus
extern "C" {
#endif

struct hc_destructor {
    void *user_pointer;

    void (*destructor)(void *user_pointer, void *data);
};

#ifdef __cplusplus
}
#endif

#endif // HC_DESTRUCTOR_H
