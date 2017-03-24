//Librerias Nesesarias
#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>
#include <AP_HAL.h>
#include <AP_HAL_AVR.h>
const AP_HAL::HAL& hal = AP_HAL_AVR_APM2;
//Mandamos a activar el sensor
AP_InertialSensor_MPU6000 ins;
//Definimos variables para guardar el valor de los angulos de euler
float roll;
float pitch;
float yaw;

void setup()
{
    ins.init(AP_InertialSensor::COLD_START,  AP_InertialSensor::RATE_100HZ, NULL);
    hal.scheduler->suspend_timer_procs();
    ins.dmp_init();
    ins.push_gyro_offsets_to_dmp();
    hal.scheduler->resume_timer_procs();
}

void loop()
{
  while (ins.num_samples_available() == 0);
    ins.update();
    ins.quaternion.to_euler(&roll, &pitch, &yaw);
    roll  = ToDeg(roll) ;
    pitch = ToDeg(pitch) ;
    yaw   = ToDeg(yaw) ;
    hal.console->printf_P(
    PSTR("P:%4.1f  R:%4.1f Y:%4.1f\n"), pitch,roll,yaw);
}
AP_HAL_MAIN();
