#ifndef TRAFFIC_LIGHTS_H
#define TRAFFIC_LIGHTS_H

void init(unsigned char *lights);
void turn_on(unsigned char *lights, unsigned char light_num);
void turn_off(unsigned char *lights, unsigned char light_num);
void next_step(unsigned char *lights);
void reverse(unsigned char *lights);
void swap(unsigned char *lights_1, unsigned char *lights_2);

#endif /* !TRAFFIC_LIGHTS_H */
