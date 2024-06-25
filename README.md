# Bedrockix
Prevent Minecraft: Bedrock Edition from suspending.

## Usage
- Run the following script in PowerShell to add Bedrockix to startup:

    ```powershell
    $ProgressPreference = "SilentlyContinue"
    $Path = [System.Environment]::GetFolderPath("Startup", "Create")
    Invoke-RestMethod "https://github.com/Aetopia/Bedrockix/releases/latest/download/Bedrockix.exe" -OutFile "$Path\Bedrockix.exe"
    & "$Path\Bedrockix.exe"
    $ProgressPreference = "Continue"
    ```
> [!IMPORTANT]
> - The fix persists even when Minecraft: Bedrock Edition is updated.
> - The fix only applies if Minecraft or Minecraft Preview is installed.
> - The fix only remains active until you sign out.

# Build
1. Install [`GCC i686`](https://winlibs.com/) and [`UPX`](https://upx.github.io/) for optional compression.
2. Run `Build.cmd`.