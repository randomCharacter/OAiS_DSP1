#ifndef PARAM_REVERB_H_
#define PARAM_REVERB_H_

extern void param_reverb_init(Int16* buffer, Int16 buf_size, Int16* read_index, Int16* write_index, Int16 n);
extern Int16 param_reverb(Int16 input, Int16* buffer, Int16 buf_size, Int16* read_index, Int16* write_index, Int16 gain);


#endif /* PARAM_REVERB_H_ */
