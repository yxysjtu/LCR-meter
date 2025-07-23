#include "ti_msp_dl_config.h"

#include "seracc.h"

static void spi_transmit_8(uint8_t *data, uint8_t size)
{
    for (size_t i = 0; i != size; ++i) {
        while (DL_SPI_isBusy(SPI_DDS_INST))
            ;
        DL_SPI_transmitData8(SPI_DDS_INST, data[i]);
    }
    while (DL_SPI_isBusy(SPI_DDS_INST))
        ;
}

void spi_handler(uint8_t* data, size_t size)
{
    spi_transmit_8(data, size);
}

static uint8_t i2c_transmit(uint8_t addr, const uint8_t* data, size_t size)
{
    uint8_t result = 0;

    /* Wait for I2C to be Idle */
    while (!(
        DL_I2C_getControllerStatus(I2C0) & DL_I2C_CONTROLLER_STATUS_IDLE))
        ;

    /* Send the packet to the controller.
     * This function will send Start + Stop automatically.
     */
    DL_I2C_startControllerTransfer(I2C0, addr,
        DL_I2C_CONTROLLER_DIRECTION_TX, size);

    /* Trap if there was an error */
    if (DL_I2C_getControllerStatus(I2C0) &
        DL_I2C_CONTROLLER_STATUS_ERROR) {
        /* LED will remain high if there is an error */
        result = 1;
    }

    if (!result)
    {
        for (size_t i = 0; i != size; ++i)
        {
            while (DL_I2C_isControllerTXFIFOFull(I2C0))
                ;
            DL_I2C_transmitControllerData(I2C0, data[i]);
        }

        /* Poll until the Controller writes all bytes */
        while (DL_I2C_getControllerStatus(I2C0) &
            DL_I2C_CONTROLLER_STATUS_BUSY_BUS)
            ;

        /* Trap if there was an error */
        if (DL_I2C_getControllerStatus(I2C0) &
            DL_I2C_CONTROLLER_STATUS_ERROR) {
            /* LED will remain high if there is an error */
            result = 1;
        }

        /* Wait for I2C to be Idle */
        while (!(
            DL_I2C_getControllerStatus(I2C0) & DL_I2C_CONTROLLER_STATUS_IDLE))
            ;
    }

    return result;
}

static uint8_t i2c_receive(uint8_t addr, uint8_t* data, size_t size)
{
    uint8_t result = 0;

    /* Send a read request to Target */
    DL_I2C_startControllerTransfer(I2C0, addr,
        DL_I2C_CONTROLLER_DIRECTION_RX, size);

    /* Trap if there was an error */
    if (DL_I2C_getControllerStatus(I2C0) &
        DL_I2C_CONTROLLER_STATUS_ERROR) {
        /* LED will remain high if there is an error */
        result = 1;
    }

    if (!result)
    {
        /*
        * Receive all bytes from target. LED will remain high if not all bytes
        * are received
        */
        for (uint8_t i = 0; i < size; i++) {
            while (DL_I2C_isControllerRXFIFOEmpty(I2C0))
                ;
            data[i] = DL_I2C_receiveControllerData(I2C0);
        }
    }

    return result;
}

void i2c_handler(uint8_t* data, size_t size)
{
  if (size < 3)
    return;
  uint8_t addr = data[1];
  if (data[0] == 'W')
  {
    uint8_t result = i2c_transmit(addr, data+2, size-2);
    seracc_transmit(&result, 1);
  }
  else if (data[0] == 'R')
  {
    uint8_t result[data[2]+1];
    result[0] = i2c_receive(addr, result+1, data[2]);
    seracc_transmit(result, data[2]+1);
  }
}

