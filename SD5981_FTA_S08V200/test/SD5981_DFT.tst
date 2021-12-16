<?xml version="1.0" encoding="UTF-8" ?>
<tests>
    <test name="POWER_OSD" type="Test" timing="" level="" pattern="" power="" comment="">
        <testclass name="libHiLink16LRV100_tml.POWER_OSD">
            <propvalues>
                <propvalue name="powerpinlist" value="" />
            </propvalues>
        </testclass>
    </test>
    <test name="OS_PS_FTA" type="Test" timing="" level="OS_PS" pattern="" power="OS_PS" comment="">
        <testclass name="libHiLink16LRV100_tml.Basic_00_PowerShort">
            <propvalues>
                <propvalue name="powerpinlist" value="" />
                <propvalue name="VForce" value="0.1" />
                <propvalue name="IClampL" value="-0.025" />
                <propvalue name="IClampH" value="0.025" />
                <propvalue name="waittime" value="0.001" />
                <propvalue name="SampleSize" value="16" />
            </propvalues>
        </testclass>
    </test>
    <test name="OS_VDD_PPMU_FTA" type="Test" timing="" level="" pattern="" power="OS_PPMU" comment="">
        <testclass name="libHiLink16LRV100_tml.Basic_02_OS_PPMU">
            <propvalues>
                <propvalue name="IO_VDDpinlist" value="OS_VDD_FTA" />
                <propvalue name="IForce" value="0.0001" />
                <propvalue name="waittime" value="0.002" />
                <propvalue name="SampleSize" value="4" />
            </propvalues>
        </testclass>
    </test>
    <test name="OS_VSS_PPMU_FTA" type="Test" timing="" level="" pattern="" power="OS_PPMU" comment="">
        <testclass name="libHiLink16LRV100_tml.Basic_02_OS_PPMU">
            <propvalues>
                <propvalue name="IO_VDDpinlist" value="OS_VDD_FTA" />
                <propvalue name="IForce" value="-0.0001" />
                <propvalue name="waittime" value="0.002" />
                <propvalue name="SampleSize" value="4" />
            </propvalues>
        </testclass>
    </test>
    <test name="OS_VDD_PPMU_SDS_FTA" type="Test" timing="" level="" pattern="" power="OS_PPMU" comment="">
        <testclass name="libHiLink16LRV100_tml.Basic_02_OS_PPMU">
            <propvalues>
                <propvalue name="IO_VDDpinlist" value="OS_SDS" />
                <propvalue name="IForce" value="0.0002" />
                <propvalue name="waittime" value="0.002" />
                <propvalue name="SampleSize" value="4" />
            </propvalues>
        </testclass>
    </test>
    <test name="OS_VSS_PPMU_SDS_FTA" type="Test" timing="" level="" pattern="" power="OS_PPMU" comment="">
        <testclass name="libHiLink16LRV100_tml.Basic_02_OS_PPMU">
            <propvalues>
                <propvalue name="IO_VDDpinlist" value="OS_SDS" />
                <propvalue name="IForce" value="-0.0002" />
                <propvalue name="waittime" value="0.002" />
                <propvalue name="SampleSize" value="4" />
            </propvalues>
        </testclass>
    </test>
</tests>
