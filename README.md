# voice-filters

This repo is for the open source DSP filters made for alt:V.

## Editing & building

Run generate.bat and find the Visual Studio project files in the BUILD\VS2019 folder.

## Coding guidelines

Create a new folder in filters and place the source files there, based on your filter name. E.g. `filters/YourFilter/YourFilter.cpp`
`filters/YourFilter/YourFilter.h`

Create your own class in YourFilter.h based on alt::IAudioFilter

    class YourFilter : public alt::IAudioFilter

Override the Process method from the base class, that is where the math with pcm data happens.

    void Process(pcmSample* data, uint32_t size) override;
**Make sure your cpp file contains most of the source code, the header should contain the class and declarations only**

In main.cpp include your filter's header and place the creation code in the exported CreateFilter code.

    if(nameHash == IAudioFilter::hash("YourFilter"))
        return new YourFilter();

An example DSP filter, MuteChannel has been added as an example.
**Once you are done, test your filter and submit a pull request.**

## Testing your filter

**The filter tester supports WAV input only, 44.1 KHz 2 channels**

A filter tester was uploaded in this repository in the test folder. Place your voice-filters.dll in the test folder and use the filter-tester.exe with the following command line args:

`filter-tester.exe input <input file name> output <output file name> filter <filter name> <paramname>=<value> `

Example:
`filter-tester.exe input input.wav output output.wav filter MuteChannel isLeft=true`

The command above takes a wav file as input and runs the example MuteChannel filter on it, with the isLeft parameter for the filter set to true. When the process is finished, it will produce the output.wav file. Multiple filter parameters can be used, the app automatically parses the parameters for it.


