
open Utils;
open HeaderStyles;

[@react.component]
let make = () => {
    <header className=Style.header>
        <div className=Style.headerRow>
            <div className=Style.headerInner>
                <a href="https://github.com/alfinsuryaS/reason-rust-scrapper" target="blank"><i className="fa fa-github"></i>(str(" Open Github"))</a>
                <nav className=Style.navigation>
                    <ul>
                        <li><Link href="/">(str("Home"))</Link></li>
                        <li><Link href="/#/data/">(str("Data"))</Link></li>
                    </ul>
                </nav>
            </div>
        </div>
    </header>
}