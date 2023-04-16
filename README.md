# Smart Garden System :seedling::deciduous_tree:

## Sensors Used: 
- Soil moisture sensor
- GY-30 BH1750FVI Digital Ambient Light Intensity Sensor Module



## Bluetooth Routes:

To request or send information to the Iot system, you can send payload using this format:

```json
{
    "route":"#ROUTE_NAME_HERE",
    "body":{
        "#PAYLOAD_FOR_ROUTE"
    }
}
```

### Routes Availabe:


| Type   |      Route      |  Details |
|----------|:-------------:|------:|
| GET |    getConfig   |  Return current configuration |
| PUT | setConfig |   Responsible for receive the new configuration|
| PUT | forceWatering |   Responsible for enable watering manual|

## Libraries Used:

- Manipulate JSON : [arduinojson](https://arduinojson.org/?utm_source=meta&utm_medium=library.properties)
- Manage GY-30 BH1750FVI : [BH1750](https://github.com/claws/BH1750)