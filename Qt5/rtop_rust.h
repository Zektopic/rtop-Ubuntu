#ifndef RTOP_RUST_H
#define RTOP_RUST_H

#ifdef __cplusplus
extern "C" {
#endif

const char* get_system_metrics_json();
void free_string(char* s);

#ifdef __cplusplus
}
#endif

#endif // RTOP_RUST_H
