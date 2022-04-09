# dicom-to-json

The nodejs dcm2json native modules of dcmtk.

# Complier environment
- nodejs v14.15.0

## Windows
- Windows 10 64bits (vs 2019)

## Linux
- Ubuntu 20.04 (g++ 9.3.0)

### Install iconv
Before using, you must install the iconv
- download iconv
```sh
wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.16.tar.gz
```
- tar gz
```sh
tar zxvf libiconv-1.16.tar.gz
```
- config
```
cd libiconv-1.16 \
./configure --prefix=/usr/local/apps
```
- complier
```sh
sudo make && sudo make install
```

# Troubleshooting
## F: Unknown VR: Tag not found in data dictionary: converting file to UTF-8:
- The DCMDICTPATH environment variable is not set.
- You can run command below
```sh
export DCMDICTPATH=$(pwd)/dmcdata/data/dicom.dic
```

# example
## dcm2json
```js
const { dcm2json } = require("dicom-to-json");
const path=  require('path');

dcm2json(path.join(__dirname, "/000001.dcm") , function (json) {
    console.log(json);
})
```
### output
<details>
    <summary>click to show</summary>

  ```json
  I: M:\nodejs\dicom-module-converter\example\0003.dcm
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
I: converting all element values that are affected by SpecificCharacterSet (0008,0005) to UTF-8
I: get json success
{
  "00020001": {
    "vr": "OB",
    "InlineBinary": "AAE="
  },
  "00020002": {
    "vr": "UI",
    "Value": [
      "1.2.840.10008.5.1.4.1.1.12.1"
    ]
  },
  "00020003": {
    "vr": "UI",
    "Value": [
      "1.3.12.2.1107.5.4.3.284980.19951129.170916.9"
    ]
  },
  "00020010": {
    "vr": "UI",
    "Value": [
      "1.2.840.10008.1.2.4.50"
    ]
  },
  "00020012": {
    "vr": "UI",
    "Value": [
      "1.3.12.2.1107.5.4.3.2"
    ]
  },
  "00020016": {
    "vr": "AE",
    "Value": [
      "SIEMENS:DCR 1.0"
    ]
  },
  "00080005": {
    "vr": "CS",
    "Value": [
      "ISO_IR 192"
    ]
  },
  "00080008": {
    "vr": "CS",
    "Value": [
      "DERIVED",
      "PRIMARY",
      "BIPLANE A"
    ]
  },
  "00080016": {
    "vr": "UI",
    "Value": [
      "1.2.840.10008.5.1.4.1.1.12.1"
    ]
  },
  "00080018": {
    "vr": "UI",
    "Value": [
      "1.3.12.2.1107.5.4.3.284980.19951129.170916.9"
    ]
  },
  "00080020": {
    "vr": "DA",
    "Value": [
      "19930325"
    ]
  },
  "00080030": {
    "vr": "TM",
    "Value": [
      "135731"
    ]
  },
  "00080050": {
    "vr": "SH"
  },
  "00080060": {
    "vr": "CS",
    "Value": [
      "XA"
    ]
  },
  "00080070": {
    "vr": "LO"
  },
  "00080080": {
    "vr": "LO",
    "Value": [
      "INSTITUTION                 ."
    ]
  },
  "00080081": {
    "vr": "ST"
  },
  "00080090": {
    "vr": "PN"
  },
  "00081030": {
    "vr": "LO",
    "Value": [
      "8 images of 4 biplane acqs"
    ]
  },
  "00081050": {
    "vr": "PN",
    "Value": [
      {
        "Alphabetic": "Well^U^R^Dr."
      }
    ]
  },
  "00081140": {
    "vr": "SQ",
    "Value": [
      {
        "00081150": {
          "vr": "UI",
          "Value": [
            "1.2.840.10008.5.1.4.1.1.12.1"
          ]
        },
        "00081155": {
          "vr": "UI",
          "Value": [
            "1.3.12.2.1107.5.4.3.284980.19951129.170916.11"
          ]
        }
      }
    ]
  },
  "00082110": {
    "vr": "CS",
    "Value": [
      "01"
    ]
  },
  "00082112": {
    "vr": "SQ",
    "Value": [
      {
        "00081150": {
          "vr": "UI",
          "Value": [
            "1.2.840.10008.5.1.4.1.1.12.1"
          ]
        },
        "00081155": {
          "vr": "UI",
          "Value": [
            "1.3.12.2.1107.5.4.3.284980.19951129.170916.8"
          ]
        }
      }
    ]
  },
  "00090010": {
    "vr": "LO",
    "Value": [
      "CARDIO-SMS 1.0"
    ]
  },
  "00091002": {
    "vr": "OB",
    "InlineBinary": "AAAAAQAAAAEAAAAAAAAAAQAAAAAAAAABAAAAAAAAAAEAAAABAAAAAAAAAAAAAAADAAAA/wAAAAAAAAB/AAAA/wAAAAEAAAAAAAAAAAAAAAAAAAADAAAACAAAAAEAAAAAAAAAAAAAAAAAAAADAAAACC0tLS0tLS0tLgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADMyMi0yOTItNzMtNgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADE5NTgwNzE5AAAzNAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABGAAAAAAAAAAAAAAAAAAAAAABJTlNUSVRVVElPTgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAtLS0tLS0tLS0tLS4AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAxOTkzMDMyNQAAMTM1NzMxAAAAAAAAAAAAAAAAMTk5MzAzMjUAADEzNTczMQAAAAAAAAAAAAAAADggaW1hZ2VzIG9mIDQgYmlwbGFuZSBhY3FzAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABTTVNSQTAwMzM1AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAAAAIAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAACAAABEQAAAAAxLjMuMTIuMi4xMTA3LjUuNC4zLjQ5NzUzMTY3NzcyMTYuMTk5NTExMTQuOTQxMDEuMTYAAAAAAAAAAAAAAAAAAAAxLjMuMTIuMi4xMTA3LjUuNC4zLjQ5NzUzMTY3NzcyMTYuMTk5NTExMTQuOTQxMDEuMTcAAAAAAAAAAAAAAAAAAAAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=="
  },
  "00091003": {
    "vr": "OB",
    "InlineBinary": "AAAAATE5OTMwMzI1AAAxMzU3MzEAAAAAAAAAAAAAAAAxOTkzMDMyNQAAMTM1NzMxAAAAAAAAAAAAAAAASGljb3IgRENNAAAAAAAAAAAAAAAAAAAAAAAAAQAAAAAAAAABARE0WAAAAAUBETRYAR8C/AAAANgAAAAEARE6aAAAAAEAAAADAAAAAAAAAAAAAAAAAAAABQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/wAAAAAAAAAAAAAAAAAAABEAAAABAAAAQQAAAAAAAAAAAAAF3AAAAAEAAAAAAAAAAAAAAAAAAAABAAAAAQAAASr///zbAAABHQAAAAMAAADQAAAA0QAAA4gAAAOZAAAEFQAAAAAAAAAAAAAGFgAACrwAAAAtAAAAAAAAAAAAAAAAAAAAAQAAAAEAAAAAAAAAAQAAAAcAAAAAAAAAAAAAAAAAAAABAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACIAAAACAAAABAAAAAAAAAD/AAAAAAAAAAQAAAAAAAAA/wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAAAAAAAAABARE1/AAAAAUBETX8"
  },
  "00091005": {
    "vr": "OB",
    "InlineBinary": "AAAFUAAAABEAAAAEAAAEsAAAAFAAAAAC"
  },
  "00100010": {
    "vr": "PN",
    "Value": [
      {
        "Alphabetic": "Rubo DEMO"
      }
    ]
  },
  "00100020": {
    "vr": "LO",
    "Value": [
      "322-292-73-6"
    ]
  },
  "00100030": {
    "vr": "DA",
    "Value": [
      "19580719"
    ]
  },
  "00100040": {
    "vr": "CS",
    "Value": [
      "F"
    ]
  },
  "00180060": {
    "vr": "DS"
  },
  "00181063": {
    "vr": "DS",
    "Value": [
      66
    ]
  },
  "00181152": {
    "vr": "IS"
  },
  "00181155": {
    "vr": "CS",
    "Value": [
      "GR"
    ]
  },
  "00181500": {
    "vr": "CS"
  },
  "00181510": {
    "vr": "DS",
    "Value": [
      29.8
    ]
  },
  "00181511": {
    "vr": "DS",
    "Value": [
      28.5
    ]
  },
  "00190010": {
    "vr": "LO",
    "Value": [
      "CARDIO-D.R. 1.0"
    ]
  },
  "00191030": {
    "vr": "UL",
    "Value": [
      262144
    ]
  },
  "0020000D": {
    "vr": "UI",
    "Value": [
      "1.3.12.2.1107.5.4.3.4975316777216.19951114.94101.16"
    ]
  },
  "0020000E": {
    "vr": "UI",
    "Value": [
      "1.3.12.2.1107.5.4.3.4975316777216.19951114.94101.17"
    ]
  },
  "00200010": {
    "vr": "SH"
  },
  "00200011": {
    "vr": "IS",
    "Value": [
      1
    ]
  },
  "00200013": {
    "vr": "IS"
  },
  "00200020": {
    "vr": "CS"
  },
  "00210010": {
    "vr": "LO",
    "Value": [
      "CARDIO-D.R. 1.0"
    ]
  },
  "00211013": {
    "vr": "IS",
    "Value": [
      5
    ]
  },
  "00280002": {
    "vr": "US",
    "Value": [
      1
    ]
  },
  "00280004": {
    "vr": "CS",
    "Value": [
      "MONOCHROME2"
    ]
  },
  "00280008": {
    "vr": "IS",
    "Value": [
      17
    ]
  },
  "00280009": {
    "vr": "AT",
    "Value": [
      "00181063"
    ]
  },
  "00280010": {
    "vr": "US",
    "Value": [
      512
    ]
  },
  "00280011": {
    "vr": "US",
    "Value": [
      512
    ]
  },
  "00280100": {
    "vr": "US",
    "Value": [
      8
    ]
  },
  "00280101": {
    "vr": "US",
    "Value": [
      8
    ]
  },
  "00280102": {
    "vr": "US",
    "Value": [
      7
    ]
  },
  "00280103": {
    "vr": "US",
    "Value": [
      0
    ]
  },
  "00281040": {
    "vr": "CS",
    "Value": [
      "LIN"
    ]
  },
  "00281090": {
    "vr": "CS",
    "Value": [
      "NAT"
    ]
  },
  "00286040": {
    "vr": "US",
    "Value": [
      1,
      12
    ]
  },
  "00286100": {
    "vr": "SQ",
    "Value": [
      {
        "00286101": {
          "vr": "CS",
          "Value": [
            "NONE"
          ]
        },
        "00286110": {
          "vr": "US",
          "Value": [
            0
          ]
        }
      }
    ]
  },
  "00290010": {
    "vr": "LO",
    "Value": [
      "CARDIO-D.R. 1.0"
    ]
  },
  "00291000": {
    "vr": "SQ",
    "Value": [
      {
        "00290010": {
          "vr": "LO",
          "Value": [
            "CARDIO-D.R. 1.0"
          ]
        },
        "00291001": {
          "vr": "US",
          "Value": [
            5,
            5
          ]
        },
        "00291002": {
          "vr": "US",
          "Value": [
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1,
            1
          ]
        },
        "00291003": {
          "vr": "FL",
          "Value": [
            0.5
          ]
        }
      }
    ]
  },
  "50000005": {
    "vr": "US",
    "Value": [
      2
    ]
  },
  "50000010": {
    "vr": "US",
    "Value": [
      1360
    ]
  },
  "50000020": {
    "vr": "CS",
    "Value": [
      "ECG"
    ]
  },
  "50000030": {
    "vr": "SH",
    "Value": [
      "DPPS",
      "NONE"
    ]
  },
  "50000103": {
    "vr": "US",
    "Value": [
      0
    ]
  },
  "50000104": {
    "vr": "US"
  },
  "50000105": {
    "vr": "US"
  },
  "50000106": {
    "vr": "US"
  },
  "50000110": {
    "vr": "US",
    "Value": [
      0,
      1
    ]
  },
  "50000112": {
    "vr": "US",
    "Value": [
      0
    ]
  },
  "50000114": {
    "vr": "US",
    "Value": [
      80
    ]
  },
  "50003000": {
    "vr": "OW",
    "InlineBinary": "/wD/AP8A/wD/AP8A/wD6AOoA2wDJALgApgCQAH4AbQBgAFUATABDADgALgAmACAAGwAXABQAEgARABIAEQAQABAADwAPABIAEQAQAA8AEAARABIAFAAVABQAEgAUABUAFgAYABkAGwAdAB0AHgAfAB8AHgAgACEAIgAiACMAIgAgAB4AHgAdABwAGgAaABkAFwAUABIADwALAAsADgAPABAAEQATABYAGAAYABoAGgAbABoAGAAYABYAEwASABIAEQARABAAEAAQABEAEwAWABYAFQATABEAEAAQAA8ADgANAAsACgALABAAEwAUABQAEwARABAAEQARAA8ADAAKAAsADAAQABIAFQAXABkAGAAXABYAFgAVABUAFAATABIAEQAQABAAEQASABMAEwAUABQAFgAXABgAGQAbABwAHAAbAB4AIgAlACkAKwAtAC4AMAAzADQANwA5ADkAOgA8AD0AQABDAEMAQgA/AD0APQA9ADsAOwA5ADYANgA/AEgAUABXAFwAXwBfAGAAYABfAF0AWgBZAFgAVgBSAE4ASgBHAEQAQgBBAEIAQwBHAEwATgBOAE4ASgBHAEQAQwBCAEAAPAA4ADYANAAzADIANAA2ADUAMwA0ADUANQA4ADsAPgA/AEAAQwBFAEYASgBLAEsATABPAFMAWQBeAGIAZABlAGcAaABqAG0AbwBwAHEAcwB0AHYAdgB2AHgAeQB6AHsAewB5AHgAdgB0AHIAcABtAG0AbgBvAG8AbgBuAGwAbABuAG8AcQBxAHEAcQByAHEAcABvAG4AawBoAGcAYwBfAFwAWwBZAFYAUwBNAEgAQwBBAEAAQAA+ADsAOQA2ADMAMAAvAC8ALgAsACwALAAsACsAKgAqACoAKgAoACgAJwAmACcAKAAoACYAIwAiACAAHgAdABsAGAAUABEAEgARABEAEgASAA8ADQAMAAoACQAHAAUABAAFAAMAAwAEAAUABwAHAAYABwAJAAkACwANAA4ADgANAAwACwALAAsACwAMAA0AEgAXABwAIAAhAB8AHQAaABkAFwAYABgAFgAVABQAEwASABEADwANAAsACQAIAAYAAwABAAEAAQACAAIAAgACAAIAAgABAAAAAAAAAAAAAAABAAIAAwABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQABAAEAAAAAAAAA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"
  }
}
  ```
</details>

## dcm2xml
```js
const { dcm2xml } = require("../index");
const path=  require('path');

dcm2xml(path.join(__dirname, "/0003.dcm") , function (json) {
    console.log(json);
})
```

### output
<details>
    <summary>click to show</summary>

    ```xml
    I: M:\nodejs\dicom-module-converter\example\0003.dcm
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    W: DcmSequenceOfItems: Length of item in sequence PixelData (7fe0,0010) is odd
    I: converting all element values that are affected by SpecificCharacterSet (0008,0005) to UTF-8
    I: get xml success
    <?xml version="1.0" encoding="UTF-8"?>
    <NativeDicomModel xml:space="preserve">
    <DicomAttribute tag="00080005" vr="CS" keyword="SpecificCharacterSet">
    <Value number="1">ISO_IR 192</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080008" vr="CS" keyword="ImageType">
    <Value number="1">DERIVED</Value>
    <Value number="2">PRIMARY</Value>
    <Value number="3">BIPLANE A</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080016" vr="UI" keyword="SOPClassUID">
    <Value number="1">1.2.840.10008.5.1.4.1.1.12.1</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080018" vr="UI" keyword="SOPInstanceUID">
    <Value number="1">1.3.12.2.1107.5.4.3.284980.19951129.170916.9</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080020" vr="DA" keyword="StudyDate">
    <Value number="1">19930325</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080030" vr="TM" keyword="StudyTime">
    <Value number="1">135731</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080050" vr="SH" keyword="AccessionNumber">
    </DicomAttribute>
    <DicomAttribute tag="00080060" vr="CS" keyword="Modality">
    <Value number="1">XA</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080070" vr="LO" keyword="Manufacturer">
    </DicomAttribute>
    <DicomAttribute tag="00080080" vr="LO" keyword="InstitutionName">
    <Value number="1">INSTITUTION                 .</Value>
    </DicomAttribute>
    <DicomAttribute tag="00080081" vr="ST" keyword="InstitutionAddress">
    </DicomAttribute>
    <DicomAttribute tag="00080090" vr="PN" keyword="ReferringPhysicianName">
    </DicomAttribute>
    <DicomAttribute tag="00081030" vr="LO" keyword="StudyDescription">
    <Value number="1">8 images of 4 biplane acqs</Value>
    </DicomAttribute>
    <DicomAttribute tag="00081050" vr="PN" keyword="PerformingPhysicianName">
    <PersonName number="1">
    <Alphabetic>
    <FamilyName>Well</FamilyName>
    <GivenName>U</GivenName>
    <MiddleName>R</MiddleName>
    <NamePrefix>Dr.</NamePrefix>
    </Alphabetic>
    </PersonName>
    </DicomAttribute>
    <DicomAttribute tag="00081140" vr="SQ" keyword="ReferencedImageSequence">
    <Item number="1">
    <DicomAttribute tag="00081150" vr="UI" keyword="ReferencedSOPClassUID">
    <Value number="1">1.2.840.10008.5.1.4.1.1.12.1</Value>
    </DicomAttribute>
    <DicomAttribute tag="00081155" vr="UI" keyword="ReferencedSOPInstanceUID">
    <Value number="1">1.3.12.2.1107.5.4.3.284980.19951129.170916.11</Value>
    </DicomAttribute>
    </Item>
    </DicomAttribute>
    <DicomAttribute tag="00082110" vr="CS">
    <Value number="1">01</Value>
    </DicomAttribute>
    <DicomAttribute tag="00082112" vr="SQ" keyword="SourceImageSequence">
    <Item number="1">
    <DicomAttribute tag="00081150" vr="UI" keyword="ReferencedSOPClassUID">
    <Value number="1">1.2.840.10008.5.1.4.1.1.12.1</Value>
    </DicomAttribute>
    <DicomAttribute tag="00081155" vr="UI" keyword="ReferencedSOPInstanceUID">
    <Value number="1">1.3.12.2.1107.5.4.3.284980.19951129.170916.8</Value>
    </DicomAttribute>
    </Item>
    </DicomAttribute>
    <DicomAttribute tag="00090010" vr="LO">
    <Value number="1">CARDIO-SMS 1.0</Value>
    </DicomAttribute>
    <DicomAttribute tag="00090002" vr="OB" privateCreator="CARDIO-SMS 1.0">
    <BulkData uuid="0d49f815-b817-01ec-c0ee-12bf61601936"/>
    </DicomAttribute>
    <DicomAttribute tag="00090003" vr="OB" privateCreator="CARDIO-SMS 1.0">
    <BulkData uuid="0d49f816-b817-01ec-c0ee-12bf61601936"/>
    </DicomAttribute>
    <DicomAttribute tag="00090005" vr="OB" privateCreator="CARDIO-SMS 1.0">
    <BulkData uuid="0d49f815-b817-01ec-c0ef-12bf61601936"/>
    </DicomAttribute>
    <DicomAttribute tag="00100010" vr="PN" keyword="PatientName">
    <PersonName number="1">
    <Alphabetic>
    <FamilyName>Rubo DEMO</FamilyName>
    </Alphabetic>
    </PersonName>
    </DicomAttribute>
    <DicomAttribute tag="00100020" vr="LO" keyword="PatientID">
    <Value number="1">322-292-73-6</Value>
    </DicomAttribute>
    <DicomAttribute tag="00100030" vr="DA" keyword="PatientBirthDate">
    <Value number="1">19580719</Value>
    </DicomAttribute>
    <DicomAttribute tag="00100040" vr="CS" keyword="PatientSex">
    <Value number="1">F</Value>
    </DicomAttribute>
    <DicomAttribute tag="00180060" vr="DS" keyword="KVP">
    </DicomAttribute>
    <DicomAttribute tag="00181063" vr="DS" keyword="FrameTime">
    <Value number="1">66</Value>
    </DicomAttribute>
    <DicomAttribute tag="00181152" vr="IS" keyword="Exposure">
    </DicomAttribute>
    <DicomAttribute tag="00181155" vr="CS" keyword="RadiationSetting">
    <Value number="1">GR</Value>
    </DicomAttribute>
    <DicomAttribute tag="00181500" vr="CS" keyword="PositionerMotion">
    </DicomAttribute>
    <DicomAttribute tag="00181510" vr="DS" keyword="PositionerPrimaryAngle">
    <Value number="1">29.8</Value>
    </DicomAttribute>
    <DicomAttribute tag="00181511" vr="DS" keyword="PositionerSecondaryAngle">
    <Value number="1">28.5</Value>
    </DicomAttribute>
    <DicomAttribute tag="00190010" vr="LO">
    <Value number="1">CARDIO-D.R. 1.0</Value>
    </DicomAttribute>
    <DicomAttribute tag="00190030" vr="UL" privateCreator="CARDIO-D.R. 1.0">
    <Value number="1">262144</Value>
    </DicomAttribute>
    <DicomAttribute tag="0020000D" vr="UI" keyword="StudyInstanceUID">
    <Value number="1">1.3.12.2.1107.5.4.3.4975316777216.19951114.94101.16</Value>
    </DicomAttribute>
    <DicomAttribute tag="0020000E" vr="UI" keyword="SeriesInstanceUID">
    <Value number="1">1.3.12.2.1107.5.4.3.4975316777216.19951114.94101.17</Value>
    </DicomAttribute>
    <DicomAttribute tag="00200010" vr="SH" keyword="StudyID">
    </DicomAttribute>
    <DicomAttribute tag="00200011" vr="IS" keyword="SeriesNumber">
    <Value number="1">1</Value>
    </DicomAttribute>
    <DicomAttribute tag="00200013" vr="IS" keyword="InstanceNumber">
    </DicomAttribute>
    <DicomAttribute tag="00200020" vr="CS" keyword="PatientOrientation">
    </DicomAttribute>
    <DicomAttribute tag="00210010" vr="LO">
    <Value number="1">CARDIO-D.R. 1.0</Value>
    </DicomAttribute>
    <DicomAttribute tag="00210013" vr="IS" privateCreator="CARDIO-D.R. 1.0">
    <Value number="1">5</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280002" vr="US" keyword="SamplesPerPixel">
    <Value number="1">1</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280004" vr="CS" keyword="PhotometricInterpretation">
    <Value number="1">MONOCHROME2</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280008" vr="IS" keyword="NumberOfFrames">
    <Value number="1">17</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280009" vr="AT" keyword="FrameIncrementPointer">
    <Value number="1">00181063</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280010" vr="US" keyword="Rows">
    <Value number="1">512</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280011" vr="US" keyword="Columns">
    <Value number="1">512</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280100" vr="US" keyword="BitsAllocated">
    <Value number="1">8</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280101" vr="US" keyword="BitsStored">
    <Value number="1">8</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280102" vr="US" keyword="HighBit">
    <Value number="1">7</Value>
    </DicomAttribute>
    <DicomAttribute tag="00280103" vr="US" keyword="PixelRepresentation">
    <Value number="1">0</Value>
    </DicomAttribute>
    <DicomAttribute tag="00281040" vr="CS" keyword="PixelIntensityRelationship">
    <Value number="1">LIN</Value>
    </DicomAttribute>
    <DicomAttribute tag="00281090" vr="CS" keyword="RecommendedViewingMode">
    <Value number="1">NAT</Value>
    </DicomAttribute>
    <DicomAttribute tag="00286040" vr="US" keyword="RWavePointer">
    <Value number="1">1</Value>
    <Value number="2">12</Value>
    </DicomAttribute>
    <DicomAttribute tag="00286100" vr="SQ" keyword="MaskSubtractionSequence">
    <Item number="1">
    <DicomAttribute tag="00286101" vr="CS" keyword="MaskOperation">
    <Value number="1">NONE</Value>
    </DicomAttribute>
    <DicomAttribute tag="00286110" vr="US" keyword="MaskFrameNumbers">
    <Value number="1">0</Value>
    </DicomAttribute>
    </Item>
    </DicomAttribute>
    <DicomAttribute tag="00290010" vr="LO">
    <Value number="1">CARDIO-D.R. 1.0</Value>
    </DicomAttribute>
    <DicomAttribute tag="00290000" vr="SQ" privateCreator="CARDIO-D.R. 1.0">
    <Item number="1">
    <DicomAttribute tag="00290010" vr="LO">
    <Value number="1">CARDIO-D.R. 1.0</Value>
    </DicomAttribute>
    <DicomAttribute tag="00290001" vr="US" privateCreator="CARDIO-D.R. 1.0">
    <Value number="1">5</Value>
    <Value number="2">5</Value>
    </DicomAttribute>
    <DicomAttribute tag="00290002" vr="US" privateCreator="CARDIO-D.R. 1.0">
    <Value number="1">1</Value>
    <Value number="2">1</Value>
    <Value number="3">1</Value>
    <Value number="4">1</Value>
    <Value number="5">1</Value>
    <Value number="6">1</Value>
    <Value number="7">1</Value>
    <Value number="8">1</Value>
    <Value number="9">1</Value>
    <Value number="10">1</Value>
    <Value number="11">1</Value>
    <Value number="12">1</Value>
    <Value number="13">1</Value>
    <Value number="14">1</Value>
    <Value number="15">1</Value>
    <Value number="16">1</Value>
    <Value number="17">1</Value>
    <Value number="18">1</Value>
    <Value number="19">1</Value>
    <Value number="20">1</Value>
    <Value number="21">1</Value>
    <Value number="22">1</Value>
    <Value number="23">1</Value>
    <Value number="24">1</Value>
    <Value number="25">1</Value>
    </DicomAttribute>
    <DicomAttribute tag="00290003" vr="FL" privateCreator="CARDIO-D.R. 1.0">
    <Value number="1">0.5</Value>
    </DicomAttribute>
    </Item>
    </DicomAttribute>
    <DicomAttribute tag="50000005" vr="US">
    <Value number="1">2</Value>
    </DicomAttribute>
    <DicomAttribute tag="50000010" vr="US">
    <Value number="1">1360</Value>
    </DicomAttribute>
    <DicomAttribute tag="50000020" vr="CS">
    <Value number="1">ECG</Value>
    </DicomAttribute>
    <DicomAttribute tag="50000030" vr="SH">
    <Value number="1">DPPS</Value>
    <Value number="2">NONE</Value>
    </DicomAttribute>
    <DicomAttribute tag="50000103" vr="US">
    <Value number="1">0</Value>
    </DicomAttribute>
    <DicomAttribute tag="50000104" vr="US">
    </DicomAttribute>
    <DicomAttribute tag="50000105" vr="US">
    </DicomAttribute>
    <DicomAttribute tag="50000106" vr="US">
    </DicomAttribute>
    <DicomAttribute tag="50000110" vr="US">
    <Value number="1">0</Value>
    <Value number="2">1</Value>
    </DicomAttribute>
    <DicomAttribute tag="50000112" vr="US">
    <Value number="1">0</Value>
    </DicomAttribute>
    <DicomAttribute tag="50000114" vr="US">
    <Value number="1">80</Value>
    </DicomAttribute>
    <DicomAttribute tag="50003000" vr="OW">
    <BulkData uuid="0d4a1f19-b817-01ec-c0ef-12bf61601936"/>
    </DicomAttribute>
    <DicomAttribute tag="7FE00010" vr="OB" keyword="PixelData">
    <BulkData uuid="0d4a1f1a-b817-01ec-c0ef-12bf61601936"/>
    </DicomAttribute>
    ```
</details>